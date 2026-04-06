#pragma once

#include "Token.hpp"
#include <vector>

class Lexer {
public:
  std::vector<Token> Tokenize(const std::string &input);

private:
};
