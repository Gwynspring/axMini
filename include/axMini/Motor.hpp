#pragma once

#include "AutomationObject.hpp"
#include "VariableEngine.hpp"
#include <string>

class Motor : public AutomationObject {
public:
  Motor(VariableEngine &var_engine, std::string name);

  void Start();
  void Stop();
  void SetSpeed(int speed);
  void Update() override;

private:
  VariableEngine &var_engine_;
  std::string name_;
};
