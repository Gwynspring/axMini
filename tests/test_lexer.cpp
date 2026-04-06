#include "axMini/Lexer.hpp"
#include "axMini/Token.hpp"
#include <cassert>
#include <iostream>
#include <vector>

#define assertm(exp, msg) assert((void(msg), exp))

int main() {
  std::string input = "VAR motor_speed : INT = 0;";

  Lexer lex;
  std::vector<Token> t = lex.Tokenize(input);

  assert(t.at(0).token_type == TokenType::kKeyWord);
  std::cout << "Checkpoint #1\n";

  assert(t.at(0).value == "VAR");
  std::cout << "Checkpoint #2\n";

  assert(t.at(1).token_type == TokenType::kIdentifier);
  std::cout << "Checkpoint #3\n";

  assert(t.at(1).value == "motor_speed");
  std::cout << "Checkpoint #4\n";

  assert(t.at(5).token_type == TokenType::kIntValue);
  std::cout << "Checkpoint #5\n";

  assert(t.at(5).value == "0");
  std::cout << "Checkpoint #6\n";

  assert(t.back().token_type == TokenType::kEndOfStatement);
  std::cout << "Checkpoint #7\n";
}
