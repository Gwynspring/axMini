#include "axMini/Motor.hpp"
#include <iostream>

Motor::Motor(VariableEngine &var_engine, std::string name)
    : var_engine_(var_engine), name_(std::move(name)) {
  Variable var_speed{VariableType::kOutput, name_ + ".speed", 0};
  Variable var_running{VariableType::kOutput, name_ + ".running", false};

  var_engine_.AddVariable(var_speed);
  var_engine_.AddVariable(var_running);
}

void Motor::SetSpeed(int speed) {
  var_engine_.WriteVariable(name_ + ".speed", speed);
}

void Motor::Start() { var_engine_.WriteVariable(name_ + ".running", true); }

void Motor::Stop() { var_engine_.WriteVariable(name_ + ".running", false); }

void Motor::Update() {
  auto var = var_engine_.GetVariable(name_ + ".running");
  if (!var.has_value()) {
    std::cout << "No Variable found\n";
    return;
  }
  if (std::get<bool>(var->value) == true) {
    std::cout << name_ << " is running\n";
  } else {
    std::cout << name_ << " is not running\n";
  }
}
