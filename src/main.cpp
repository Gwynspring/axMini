#include "axMini/AutomationFactory.hpp"
#include "axMini/ExecutionEngine.hpp"
#include "axMini/Lexer.hpp"
#include "axMini/Logger.hpp"
#include "axMini/Parser.hpp"
#include "axMini/VariableEngine.hpp"
#include "httplib.h"
#include "nlohmann/json.hpp"
#include <chrono>
#include <stop_token>
#include <thread>

int main() {

  Logger::Init();

  std::string dsl =
      "MOTOR motor_1;\n"
      "VALVE valve_1;\n"
      "IF motor_1.speed > 100 THEN valve_1.is_open = true; END_IF;\n";

  VariableEngine engine;
  AutomationFactory factory;
  httplib::Server svr;

  auto tokens = Lexer::Tokenize(dsl);
  auto declarations = Parser::ParseObjectDeclarations(tokens);
  auto objects = factory.Create(declarations, engine);
  auto if_statements = Parser::ParseIfStatement(tokens);

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

  std::jthread scan_thread(
      [&objects, &engine, &if_statements](std::stop_token st) {
        ExecutionEngine exec(engine);
        while (!st.stop_requested()) {
          exec.Execute(if_statements);
          for (const auto &obj : objects) {
            obj->Update();
          }
          std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
      });

  svr.listen("0.0.0.0", 8080);
  return 0;
}
