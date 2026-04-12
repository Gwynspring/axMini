#pragma once

#include "AutomationObject.hpp"
#include "VariableEngine.hpp"
#include <string>
class Valve : public AutomationObject {
public:
  Valve(VariableEngine &var_engine, std::string name);
  void Open();
  void Close();
  bool IsOpen() const;
  void Update() override;

private:
  VariableEngine &var_engine_;
  std::string name_;
};
