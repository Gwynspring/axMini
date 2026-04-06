#include "axMini/VariableEngine.hpp"
#include "httplib.h"
#include "nlohmann/json.hpp"

int main() {
  VariableEngine engine;
  httplib::Server svr;

  Variable input(VariableType::Input, "input_test", 42);
  Variable output(VariableType::Output, "output_test", true);

  engine.AddVariable(input);
  engine.AddVariable(output);

  svr.Get("/variables/:name",
          [&engine](const httplib::Request &req, httplib::Response &res) {
            std::string name = req.path_params.at("name");

            auto it = engine.GetVariable(name);
            std::string str_val;

            std::string json;
            if (it.has_value()) {
              auto val = it->value;

              if (std::holds_alternative<int>(val)) {
                str_val += std::to_string(get<int>(val));
              }

              if (std::holds_alternative<float>(val)) {
                str_val += std::to_string(get<float>(val));
              }

              if (std::holds_alternative<bool>(val)) {
                str_val += std::to_string(get<bool>(val));
              }

              json += "{\"name\": \"" + it->name + "\", \"value\": \"" +
                      str_val + "\"}";

              res.set_content(json, "application/json");
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
      }

      res.status = success ? 200 : 404;
      res.set_content(body.dump(), "application/json");

    } catch (const nlohmann::json::parse_error &e) {
      res.set_content("{\"error\": \"invalid JSON\"}", "application/json");
      return;
    }
  });

  svr.listen("0.0.0.0", 8080);
  return 0;
}
