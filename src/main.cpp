#include "httplib.h"
#include <iostream>

int main(int argc, char *argv[]) {

  httplib::Server svr;

  svr.Get("/variables/test", [](const httplib::Request &,
                                httplib::Response &res) {
    res.set_content("{\"name\": \"test\", \"value\": 42}", "application/json");
  });

  svr.listen("0.0.0.0", 8080);
  return 0;
}
