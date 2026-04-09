
#include "axMini/Lexer.hpp"
#include "axMini/Parser.hpp"
#include <string>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../lib/doctest/doctest.h"

TEST_CASE("test parser") {
  std::string input_int = "VAR motor_speed : INT = 42;";
  std::string input_float = "VAR motor_speed : FLOAT = 42.42;";
  std::string input_bool = "VAR motor_speed : BOOL = true;";

  Lexer lex;
  std::vector<Token> t = lex.Tokenize(input_int);

  Parser p;

  std::vector<VarDeclaration> vd = p.Parse(t);
  CHECK(vd.at(0).name == "motor_speed");
  CHECK(std::get<int>(vd.at(0).initial_value) == 42);

  t = lex.Tokenize(input_float);
  vd = p.Parse(t);
  CHECK(vd.at(0).name == "motor_speed");
  CHECK(std::get<float>(vd.at(0).initial_value) == doctest::Approx(42.42f));

  t = lex.Tokenize(input_bool);
  vd = p.Parse(t);
  CHECK(vd.at(0).name == "motor_speed");
  CHECK(std::get<bool>(vd.at(0).initial_value) == true);
}
