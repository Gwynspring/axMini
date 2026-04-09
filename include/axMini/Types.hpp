#pragma once

#include <optional>
#include <string>

enum class TokenType {
  kKeyWord,
  kObjectKeyWord,
  kIdentifier,
  kType,
  kColon,
  kEquals,
  kEndOfStatement,
  kIntValue,
  kFloatValue,
  kBoolValue,
};

enum class VariableType {
  kInput,
  kOutput,
  kIntern,
};

enum class ObjectType { kMotor, kValve };

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

inline std::optional<ObjectType> ObjectTypeFromString(const std::string &s) {
  if (s == "MOTOR") {
    return ObjectType::kMotor;
  } else if (s == "VALVE") {
    return ObjectType::kValve;
  }
  return std::nullopt;
}
