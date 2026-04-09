#pragma once

#include "axMini/VariableEngine.hpp"
#include <string>

class Motor {
public:
  Motor(VariableEngine &var_engine, std::string name);

  void Start();
  void Stop();
  void SetSpeed(int speed);

private:
  VariableEngine &var_engine_;
  std::string name_;
};
