#include "axMini/Variable.hpp"
#include "axMini/VariableEngine.hpp"
#include "httplib.h"
#include <string>

int main(int argc, char *argv[]) {
  VariableEngine engine;
  httplib::Server svr;

  Variable input{VariableType::Input, "input_test", 42};
  Variable output{VariableType::Output, "output_test", true};

  engine.AddVariable(input);
  engine.AddVariable(output);

  svr.Get("/variables/test",
          [&engine](const httplib::Request &, httplib::Response &res) {
            auto it = engine.GetVariable("input_test");
            std::string json;
            if (it.has_value()) {
              json += "{\"name\": \"" + it->name + "\", \"value\": 42}";
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
