#include "axMini/VariableEngine.hpp"
#include <mutex>

void VariableEngine::AddVariable(const Variable &var) {
  std::lock_guard<std::mutex> lock(mutex_);
  variable_.try_emplace(var.name, var);
}

std::optional<Variable>
VariableEngine::GetVariable(const std::string &name) const {

  std::lock_guard<std::mutex> lock(mutex_);
  auto it = variable_.find(name);

  if (it != variable_.end())
    return it->second;
  else
    return std::nullopt;
}

bool VariableEngine::WriteVariable(const std::string &name,
                                   const std::variant<int, float, bool> &val) {

  std::lock_guard<std::mutex> lock(mutex_);
  auto it = variable_.find(name);

  if (it != variable_.end()) {
    it->second.value = val;
    return true;
  }
  return false;
}
