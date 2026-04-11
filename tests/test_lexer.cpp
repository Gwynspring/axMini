#include "axMini/Lexer.hpp"
#include <string>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../lib/doctest/doctest.h"

TEST_CASE("test lexer") {
  std::string input_int = "VAR motor_speed : INT = 42;";
  std::string input_float = "VAR motor_speed : FLOAT = 42.42;";
  std::string input_bool = "VAR motor_speed : BOOL = true;";
  std::string input_invalid = "VER motor_speed : BOOL = true;";
  std::string input_multi = "VAR motor_speed : INT = 42;\n"
                            "VAR valve_open : BOOL = false;";
  std::string input_empty = "";
  std::string input_whitespace = "   \t\n  ";

  std::vector<Token> t = Lexer::Tokenize(input_int);

  CHECK(t.at(0).token_type == TokenType::kKeyWord);
  CHECK(t.at(0).value == "VAR");
  CHECK(t.at(1).token_type == TokenType::kIdentifier);
  CHECK(t.at(1).value == "motor_speed");
  CHECK(t.at(5).token_type == TokenType::kIntValue);
  CHECK(t.at(5).value == "42");
  CHECK(t.back().token_type == TokenType::kEndOfStatement);

  t = Lexer::Tokenize(input_float);

  CHECK(t.at(0).token_type == TokenType::kKeyWord);
  CHECK(t.at(0).value == "VAR");
  CHECK(t.at(1).token_type == TokenType::kIdentifier);
  CHECK(t.at(1).value == "motor_speed");
  CHECK(t.at(5).token_type == TokenType::kFloatValue);
  CHECK(t.at(5).value == "42.42");
  CHECK(t.back().token_type == TokenType::kEndOfStatement);

  t = Lexer::Tokenize(input_bool);

  CHECK(t.at(0).token_type == TokenType::kKeyWord);
  CHECK(t.at(0).value == "VAR");
  CHECK(t.at(1).token_type == TokenType::kIdentifier);
  CHECK(t.at(1).value == "motor_speed");
  CHECK(t.at(5).token_type == TokenType::kBoolValue);
  CHECK(t.at(5).value == "true");
  CHECK(t.back().token_type == TokenType::kEndOfStatement);

  t = Lexer::Tokenize(input_empty);
  CHECK(t.empty() == true);

  t = Lexer::Tokenize(input_whitespace);
  CHECK(t.empty() == true);

  t = Lexer::Tokenize(input_multi);
  CHECK(t.size() == 14);
  CHECK(t.at(6).token_type == TokenType::kEndOfStatement);
  CHECK(t.at(7).token_type == TokenType::kKeyWord);
  CHECK(t.at(13).token_type == TokenType::kEndOfStatement);

  t = Lexer::Tokenize(input_empty);
  CHECK(t.size() == 0);

  t = Lexer::Tokenize(input_whitespace);
  CHECK(t.size() == 0);
}
