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
  Variable(VariableType typ, std::string n, std::variant<int, float, bool> val)
      : variable_typ(typ), name(std::move(n)), value(std::move(val)) {}
  static std::string variableTypeToString(VariableType type) {
    switch (type) {
    case VariableType::Input:
      return "Input";
    case VariableType::Output:
      return "Output";
    case VariableType::Intern:
      return "Intern";
    }
    __builtin_unreachable();
  }
};
