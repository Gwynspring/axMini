#include "axMini/Variable.hpp"
#include "axMini/VariableEngine.hpp"
#include "httplib.h"

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

  svr.listen("0.0.0.0", 8080);
  return 0;
}
