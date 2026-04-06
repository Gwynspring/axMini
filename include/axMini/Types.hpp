#pragma once

enum class VariableType {
  kInput,
  kOutput,
  kIntern,
};

enum class TokenType {
  kKeyWord,
  kIdentifier,
  kType,
  kColon,
  kEquals,
  kValue,
  kEndOfStatement,
  kIntValue,
  kFloatValue,
  kBoolValue
};
