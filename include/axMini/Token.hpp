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
  Token(TokenType type, std::string val)
      : token_type(type), value(std::move(val)) {};
};
