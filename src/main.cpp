#include "axMini/AutomationFactory.hpp"
#include "axMini/DslRuntime.hpp"
#include "axMini/ExecutionEngine.hpp"
#include "axMini/Lexer.hpp"
#include "axMini/Logger.hpp"
#include "axMini/Parser.hpp"
#include "axMini/PersistenceManager.hpp"
#include "axMini/VariableEngine.hpp"
#include "httplib.h"
#include "nlohmann/json.hpp"
#include <chrono>
#include <stop_token>
#include <thread>

int main() {

  Logger::Init();

  std::string dsl_objects = "MOTOR motor_1;\n"
                            "VALVE valve_1;\n";

  std::string dsl_if =
      "IF motor_1.speed > 100 THEN valve_1.is_open = true; END_IF;\n"
      "IF motor_1.speed < 90 THEN valve_1.is_open = false; END_IF;\n";

  VariableEngine engine;
  DslRuntime runtime;
  PersistenceManager pers_manager(engine, runtime,
                                  std::string(AXMINI_DATA_DIR) + "/state.json");
  pers_manager.Load();
  AutomationFactory factory;
  httplib::Server svr;

  auto tokens_obj = Lexer::Tokenize(dsl_objects);
  auto declarations = Parser::ParseObjectDeclarations(tokens_obj);
  auto objects = factory.Create(declarations, engine);

  if (runtime.GetStatements().empty()) {
    auto tokens_if = Lexer::Tokenize(dsl_if);
    runtime.AddStatements(Parser::ParseIfStatement(tokens_if), dsl_if);
  }

  Variable input(VariableType::kInput, "input_test", 42);
  Variable output(VariableType::kOutput, "output_test", true);

  engine.AddVariable(input);
  engine.AddVariable(output);

  svr.Get("/variables/:name", [&engine](const httplib::Request &req,
                                        httplib::Response &res) {
    std::string name = req.path_params.at("name");

    auto it = engine.GetVariable(name);

    if (it.has_value()) {
      nlohmann::json j;
      std::visit([&j](auto val) { j["value"] = val; }, it->value);
      j["name"] = it->name;
      j["variable_typ"] = Variable::VariableTypeToString(it->variable_typ);
      res.status = 200;
      res.set_content(j.dump(), "application/json");
    } else {
      res.status = 404;
      res.set_content("{\"error\": \"variable not found\"}",
                      "application/json");
    }
  });

  svr.Post("/save", [&pers_manager](const httplib::Request &req,
                                    httplib::Response &res) {
    pers_manager.Save();
    res.status = 200;
    res.set_content("{\"status\": \"saved\"}", "application/json");
  });
  svr.Post("/dsl/if", [&runtime](const httplib::Request &req,
                                 httplib::Response &res) {
    if (req.body.empty()) {
      res.status = 400;
      res.set_content("{\"error\": \"empty input\"}", "application/json");
      return;
    }
    auto tokens = Lexer::Tokenize(req.body);
    runtime.AddStatements(Parser::ParseIfStatement(tokens), req.body);

    res.status = 200;
    res.set_content("{\"status\": \"ok\"}", "application/json");
    return;
  });

  svr.Put("/variables/:name", [&engine](const httplib::Request &req,
                                        httplib::Response &res) {
    try {
      auto body = nlohmann::json::parse(req.body);
      auto val = body["value"];

      std::string name = req.path_params.at("name");

      bool success = false;

      if (val.is_number_integer()) {
        success = engine.WriteVariable(name, val.get<int>());
      } else if (val.is_number_float()) {
        success = engine.WriteVariable(name, val.get<float>());
      } else if (val.is_boolean()) {
        success = engine.WriteVariable(name, val.get<bool>());
      } else {
        res.status = 400;
        res.set_content("{\"error\": \"unsupported value type\"}",
                        "application/json");
        return;
      }
      res.status = success ? 200 : 404;
      res.set_content(body.dump(), "application/json");

    } catch (const nlohmann::json::parse_error &e) {
      res.set_content("{\"error\": \"invalid JSON\"}", "application/json");
      return;
    }
  });

  std::jthread scan_thread([&objects, &engine, &runtime](std::stop_token st) {
    ExecutionEngine exec(engine);
    while (!st.stop_requested()) {
      exec.Execute(runtime.GetStatements());
      for (const auto &obj : objects) {
        obj->Update();
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
  });

  svr.listen("0.0.0.0", 8080);
  pers_manager.Save();
  return 0;
}
