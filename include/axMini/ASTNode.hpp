#pragma once

#include "axMini/Types.hpp"
#include <string>
#include <variant>

struct VarDeclaration {
  std::string name;
  DataType type;
  std::variant<int, float, bool> initial_value;
  VarDeclaration(std::string n, DataType t, std::variant<int, float, bool> val)
      : name(n), type(t), initial_value(val) {};
};
