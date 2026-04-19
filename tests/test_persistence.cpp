#include "axMini/DslRuntime.hpp"
#include "axMini/Lexer.hpp"
#include "axMini/Logger.hpp"
#include "axMini/Parser.hpp"
#include "axMini/PersistenceManager.hpp"
#include <filesystem>
#include <string>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../lib/doctest/doctest.h"

TEST_CASE("test persistence") {
  Logger::Init();

  auto temp_path =
      std::filesystem::temp_directory_path() / "axMini_test_state.json";

  std::string dsl =
      "MOTOR motor_1;\n"
      "VALVE valve_1;\n"
      "IF motor_1.speed > 100 THEN valve_1.is_open = true; END_IF;\n";

  VariableEngine engine;
  DslRuntime runtime;
  PersistenceManager pers_manager(engine, runtime, temp_path);

  auto tokens = Lexer::Tokenize(dsl);
  auto declarations = Parser::ParseObjectDeclarations(tokens);
  runtime.AddStatements(Parser::ParseIfStatement(tokens));

  CHECK_FALSE(std::filesystem::exists(temp_path));
  pers_manager.Load();
  CHECK(std::filesystem::exists(temp_path) == true);

  engine.AddVariable(Variable(VariableType::kInput, "test_1", true));
  engine.AddVariable(Variable(VariableType::kOutput, "test_2", 42));

  pers_manager.Save();

  VariableEngine new_engine;
  DslRuntime new_runtime;

  PersistenceManager new_pers_manager(new_engine, new_runtime, temp_path);
  new_pers_manager.Load();

  auto var = new_engine.GetVariable("test_1");
  CHECK(var.value().variable_typ == VariableType::kInput);
  CHECK(std::get<bool>(var.value().value) == true);

  var = new_engine.GetVariable("test_2");
  CHECK(var.value().variable_typ == VariableType::kOutput);
  CHECK(std::get<int>(var.value().value) == 42);

  std::filesystem::remove(temp_path);
}
