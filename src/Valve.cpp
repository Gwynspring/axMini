#include "axMini/Valve.hpp"
#include <iostream>

Valve::Valve(VariableEngine &engine, std::string name)
    : var_engine_(engine), name_(std::move(name)) {
  Variable var{VariableType::kOutput, name_ + ".is_open", false};
  var_engine_.AddVariable(var);
}

void Valve::Open() { var_engine_.WriteVariable(name_ + ".is_open", true); }
void Valve::Close() { var_engine_.WriteVariable(name_ + ".is_open", false); }
bool Valve::IsOpen() {
  auto var = var_engine_.GetVariable(name_ + ".is_open");

  if (!var.has_value()) {
    return false;
  }

  return std::get<bool>(var->value) == true;
}

void Valve::Update() {
  auto var = var_engine_.GetVariable(name_ + ".is_open");
  if (!var.has_value()) {
    std::cout << "No variable found\n";
    return;
  }
  if (std::get<bool>(var->value) == true) {
    std::cout << name_ << " is open\n";
  } else {
    std::cout << name_ << " is not open\n";
  }
}
