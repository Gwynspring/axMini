#pragma once

#include "Types.hpp"
#include <string>

struct Token {
  TokenType token_type;
  std::string value;
  Token(TokenType type, std::string val)
      : token_type(type), value(std::move(val)) {};
};
