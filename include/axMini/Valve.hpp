#pragma once

#include "axMini/AutomationObject.hpp"
#include "axMini/VariableEngine.hpp"
#include <string>
class Valve : public AutomationObject {
public:
  Valve(VariableEngine &var_engine, std::string name);
  void Open();
  void Close();
  bool IsOpen();
  void Update() override;

private:
  VariableEngine &var_engine_;
  std::string name_;
};
