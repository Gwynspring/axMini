#include "axMini/Valve.hpp"
#include "axMini/Logger.hpp"

Valve::Valve(VariableEngine &engine, std::string name)
    : var_engine_(engine), name_(std::move(name)) {
  Variable var{VariableType::kOutput, name_ + ".is_open", false};
  var_engine_.AddVariable(var);
}

void Valve::Open() { var_engine_.WriteVariable(name_ + ".is_open", true); }
void Valve::Close() { var_engine_.WriteVariable(name_ + ".is_open", false); }
bool Valve::IsOpen() const {
  auto var = var_engine_.GetVariable(name_ + ".is_open");

  if (!var.has_value()) {
    return false;
  }
  return std::get<bool>(var->value) == true;
}

void Valve::Update() {
  auto var = var_engine_.GetVariable(name_ + ".is_open");
  if (!var.has_value()) {
    Logger::Warn("No variable found");
    return;
  }
  if (std::get<bool>(var->value) == true) {
    Logger::Info(name_ + " is open");
  } else {
    Logger::Info(name_ + " is not open");
  }
}
