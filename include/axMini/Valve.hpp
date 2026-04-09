#pragma once

#include "axMini/VariableEngine.hpp"
#include <string>
class Valve {
public:
  Valve(VariableEngine &var_engine, std::string name);
  void Open();
  void Close();
  bool IsOpen();

private:
  VariableEngine &var_engine_;
  std::string name_;
};
