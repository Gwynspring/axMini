#pragma once

#include "Variable.hpp"
#include <optional>
#include <unordered_map>

class VariableEngine {
public:
  void AddVariable(const Variable &var);
  std::optional<Variable> GetVariable(const std::string &name) const;
  bool WriteVariable(const std::string &name,
                     const std::variant<int, float, bool> &val);

private:
  std::unordered_map<std::string, Variable> variable_;
};
