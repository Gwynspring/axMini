#pragma once

#include "Types.hpp"
#include <string>
#include <variant>

struct Variable {
  VariableType variable_typ;
  std::string name;
  std::variant<int, float, bool> value;
  Variable(VariableType typ, std::string n, std::variant<int, float, bool> val)
      : variable_typ(typ), name(std::move(n)), value(std::move(val)) {}
  static std::string VariableTypeToString(VariableType type) {
    switch (type) {
    case VariableType::kInput:
      return "Input";
    case VariableType::kOutput:
      return "Output";
    case VariableType::kIntern:
      return "Intern";
    }
    __builtin_unreachable();
  }
};
