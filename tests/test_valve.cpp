#include "axMini/Logger.hpp"
#include "axMini/Valve.hpp"
#include <string>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../lib/doctest/doctest.h"

TEST_CASE("test valve") {
  Logger::Init();
  VariableEngine engine;
  Valve valve_1(engine, "valve_1");

  auto var = engine.GetVariable("valve_1.is_open");
  CHECK_FALSE(std::get<bool>(var->value));

  valve_1.Open();

  var = engine.GetVariable("valve_1.is_open");
  CHECK(std::get<bool>(var->value) == true);
  CHECK(valve_1.IsOpen() == true);

  valve_1.Close();
  var = engine.GetVariable("valve_1.is_open");
  CHECK_FALSE(std::get<bool>(var->value));

  CHECK_FALSE(valve_1.IsOpen());
}
