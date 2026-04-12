#pragma once

#include "Token.hpp"
#include <string>
#include <vector>

class Lexer {
public:
  static std::vector<Token> Tokenize(const std::string &input);

private:
  static bool IsNumber(const std::string &s);
  static bool IsFloat(const std::string &s);
};
