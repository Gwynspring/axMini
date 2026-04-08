#pragma once

#include "Token.hpp"
#include <string>
#include <vector>

class Lexer {
public:
  std::vector<Token> Tokenize(const std::string &input);

private:
  bool IsNumber(const std::string &s);
};
