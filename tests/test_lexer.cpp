#include "axMini/Lexer.hpp"
#include "axMini/Parser.hpp"
#include "axMini/Token.hpp"
#include "axMini/Types.hpp"
#include <string>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../lib/doctest/doctest.h"

TEST_CASE("test lexer and parser") {
  std::string input = "VAR motor_speed : INT = 42;";

  Lexer lex;
  std::vector<Token> t = lex.Tokenize(input);

  CHECK(t.at(0).token_type == TokenType::kKeyWord);
  CHECK(t.at(0).value == "VAR");
  CHECK(t.at(1).token_type == TokenType::kIdentifier);
  CHECK(t.at(1).value == "motor_speed");
  CHECK(t.at(5).token_type == TokenType::kIntValue);
  CHECK(t.at(5).value == "42");
  CHECK(t.back().token_type == TokenType::kEndOfStatement);

  Parser p;

  std::vector<VarDeclaration> vd = p.Parse(t);

  CHECK(vd.at(0).name == "motor_speed");
  CHECK(std::get<int>(vd.at(0).initial_value) == 42);
}
