#pragma once

#include <string>
#include <variant>

enum class VariableType {
  kInput,
  kOutput,
  kIntern,
};

struct Variable {
  VariableType variable_typ;
  std::string name;
  std::variant<int, float, bool> value;
  Variable(VariableType typ, std::string n, std::variant<int, float, bool> val)
      : variable_typ(typ), name(std::move(n)), value(std::move(val)) {}
  static std::string variableTypeToString(VariableType type) {
    switch (type) {
    case VariableType::kInput:
      return "kInput";
    case VariableType::kOutput:
      return "kOutput";
    case VariableType::kIntern:
      return "kIntern";
    }
    __builtin_unreachable();
  }
};
