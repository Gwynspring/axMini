#include "axMini/Motor.hpp"
#include "axMini/Valve.hpp"
#include "axMini/VariableEngine.hpp"
#include "httplib.h"
#include "nlohmann/json.hpp"
#include <chrono>
#include <iostream>
#include <stop_token>
#include <thread>
#include <vector>

int main() {
  VariableEngine engine;
  Motor motor_1(engine, "motor_1");
  Valve valve_1(engine, "valve_1");
  httplib::Server svr;

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
      } else if (!val.is_number_integer() && !val.is_number_float() &&
                 !val.is_boolean()) {
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

  std::jthread scan_thread([&engine](std::stop_token st) {
    while (!st.stop_requested()) {
      std::vector<Variable> vars = engine.GetAllVariables();

      for (const auto &it : vars) {
        std::visit(
            [&it](auto val) { std::cout << it.name << " = " << val << "\n"; },
            it.value);
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
  });

  svr.listen("0.0.0.0", 8080);
  return 0;
}
