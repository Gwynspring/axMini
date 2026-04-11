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
  std::string input_invalid = "VER motor_speed : BOOL = true;";
  std::string input_multi = "VAR motor_speed : INT = 42;\n"
                            "VAR valve_open : BOOL = false;";

  std::vector<Token> t = Lexer::Tokenize(input_int);

  std::vector<VarDeclaration> vd = Parser::Parse(t);
  CHECK(vd.at(0).name == "motor_speed");
  CHECK(std::get<int>(vd.at(0).initial_value) == 42);

  t = Lexer::Tokenize(input_float);
  vd = Parser::Parse(t);
  CHECK(vd.at(0).name == "motor_speed");
  CHECK(std::get<float>(vd.at(0).initial_value) == doctest::Approx(42.42f));

  t = Lexer::Tokenize(input_bool);
  vd = Parser::Parse(t);
  CHECK(vd.at(0).name == "motor_speed");
  CHECK(std::get<bool>(vd.at(0).initial_value) == true);

  t = Lexer::Tokenize(input_invalid);
  vd = Parser::Parse(t);
  CHECK(vd.empty() == true);

  t = Lexer::Tokenize(input_multi);
  vd = Parser::Parse(t);
  CHECK(vd.size() == 2);
  CHECK(vd.at(0).name == "motor_speed");
  CHECK(std::get<int>(vd.at(0).initial_value) == 42);
  CHECK(vd.at(1).name == "valve_open");
  CHECK(std::get<bool>(vd.at(1).initial_value) == false);

  std::string obj_multi = "MOTOR motor_1;\n"
                          "VALVE valve_1;";
  t = Lexer::Tokenize(obj_multi);
  auto od = Parser::ParseObjectDeclarations(t);

  CHECK(od.size() == 2);
  CHECK(od.at(0).name == "motor_1");
  CHECK(od.at(0).obj_type == ObjectType::kMotor);
  CHECK(od.at(1).name == "valve_1");
  CHECK(od.at(1).obj_type == ObjectType::kValve);
}
