#pragma once

#include <optional>
#include <string>

enum class TokenType {
  kKeyWord,
  kIdentifier,
  kType,
  kColon,
  kEquals,
  kEndOfStatement,
  kIntValue,
  kFloatValue,
  kBoolValue
};

enum class VariableType {
  kInput,
  kOutput,
  kIntern,
};

enum class DataType { kInt, kFloat, kBool };

inline std::optional<DataType> DataTypeFromString(const std::string &s) {
  if (s == "INT") {
    return DataType::kInt;
  } else if (s == "FLOAT") {
    return DataType::kFloat;
  } else if (s == "BOOL") {
    return DataType::kBool;
  }
  return std::nullopt;
}
