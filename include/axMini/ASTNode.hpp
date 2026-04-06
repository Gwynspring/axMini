#pragma once

#include "axMini/Types.hpp"
#include <string>
#include <variant>

struct VarDeclaration {
  std::string name;
  VariableType type;
  std::variant<int, float, bool> initial_value;
};
