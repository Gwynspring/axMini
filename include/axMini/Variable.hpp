#pragma once

#include <string>
#include <variant>

enum class VariableType {
  Input,
  Output,
  Intern,
};

struct Variable {
  VariableType variable_typ;
  std::string name;
  std::variant<int, float, bool> value;
};
