#include "axMini/VariableEngine.hpp"
#include <mutex>
#include <vector>

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

std::vector<Variable> VariableEngine::GetAllVariables() const {
  std::lock_guard<std::mutex> lock(mutex_);
  std::vector<Variable> var;
  var.reserve(variable_.size());

  for (const auto &it : variable_) {
    var.push_back(it.second);
  }

  return var;
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
