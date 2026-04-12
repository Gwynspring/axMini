#include "axMini/ExecutionEngine.hpp"
#include "axMini/Lexer.hpp"
#include "axMini/Parser.hpp"
#include "axMini/VariableEngine.hpp"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../lib/doctest/doctest.h"

TEST_CASE("test ExecutionEngine") {
  VariableEngine engine;
  Variable speed(VariableType::kOutput, "motor_1.speed", 150);
  Variable valve(VariableType::kOutput, "valve_1.is_open", false);
  engine.AddVariable(speed);
  engine.AddVariable(valve);

  std::string dsl_gt =
      "IF motor_1.speed > 100 THEN valve_1.is_open = true; END_IF;";
  auto tokens = Lexer::Tokenize(dsl_gt);
  auto statements = Parser::ParseIfStatement(tokens);

  ExecutionEngine exec(engine);
  exec.Execute(statements);
  CHECK(std::get<bool>(engine.GetVariable("valve_1.is_open")->value) == true);

  std::string dsl_lt =
      "IF motor_1.speed < 200 THEN valve_1.is_open = false; END_IF;";
  tokens = Lexer::Tokenize(dsl_lt);
  statements = Parser::ParseIfStatement(tokens);

  exec.Execute(statements);
  CHECK_FALSE(std::get<bool>(engine.GetVariable("valve_1.is_open")->value));

  std::string dsl_eq =
      "IF motor_1.speed == 150 THEN valve_1.is_open = true; END_IF;";
  tokens = Lexer::Tokenize(dsl_eq);
  statements = Parser::ParseIfStatement(tokens);

  exec.Execute(statements);
  CHECK(std::get<bool>(engine.GetVariable("valve_1.is_open")->value) == true);

  std::string dsl_neq =
      "IF motor_1.speed == 150 THEN valve_1.is_open = false; END_IF;";
  tokens = Lexer::Tokenize(dsl_neq);
  statements = Parser::ParseIfStatement(tokens);

  exec.Execute(statements);
  CHECK_FALSE(std::get<bool>(engine.GetVariable("valve_1.is_open")->value));
}
