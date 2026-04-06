#pragma once

#include <string>

enum class TokenType {
  kKeyWord,
  kIdentifier,
  kType,
  kColon,
  kEquals,
  kValue,
  kEndOfStatement
};

struct Token {
  TokenType token_type;
  std::string value;
};
