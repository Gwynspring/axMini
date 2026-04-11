#include "axMini/Types.hpp"
#include "axMini/Variable.hpp"
#include "axMini/VariableEngine.hpp"

#include <optional>
#include <string>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../lib/doctest/doctest.h"

TEST_CASE("test engine") {
  VariableEngine engine;

  Variable var_int(VariableType::kOutput, "var_int", 42);
  Variable var_float(VariableType::kInput, "var_float", 42.42f);
  Variable var_bool(VariableType::kOutput, "var_bool", true);

  engine.AddVariable(var_int);
  auto var = engine.GetVariable("var_int");
  CHECK(var->name == "var_int");
  CHECK(var->variable_typ == VariableType::kOutput);
  CHECK(std::get<int>(var->value) == 42);

  engine.AddVariable(var_float);
  var = engine.GetVariable("var_float");
  CHECK(var->name == "var_float");
  CHECK(var->variable_typ == VariableType::kInput);
  CHECK(std::get<float>(var->value) == doctest::Approx(42.42f));

  engine.AddVariable(var_bool);
  var = engine.GetVariable("var_bool");
  CHECK(engine.GetVariable("var_bool")->name == "var_bool");
  CHECK(engine.GetVariable("var_bool")->variable_typ == VariableType::kOutput);
  CHECK(std::get<bool>(engine.GetVariable("var_bool")->value) == true);

  bool result = engine.WriteVariable("unknown variable", 42);
  CHECK_FALSE(result);

  auto no_variable = engine.GetVariable("does not exist");
  CHECK(no_variable == std::nullopt);
}
