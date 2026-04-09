#include "axMini/Motor.hpp"
#include <string>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../lib/doctest/doctest.h"

TEST_CASE("test motor") {
  VariableEngine engine;
  Motor motor_1(engine, "motor_1");

  auto var = engine.GetVariable("motor_1.speed");
  CHECK(std::get<int>(var->value) == 0);

  var = engine.GetVariable("motor_1.running");
  CHECK_FALSE(std::get<bool>(var->value));

  motor_1.SetSpeed(150);
  var = engine.GetVariable("motor_1.speed");
  CHECK(std::get<int>(var->value) == 150);

  motor_1.Start();
  var = engine.GetVariable("motor_1.running");
  CHECK(std::get<bool>(var->value) == true);

  motor_1.Stop();
  var = engine.GetVariable("motor_1.running");
  CHECK_FALSE(std::get<bool>(var->value));
}
