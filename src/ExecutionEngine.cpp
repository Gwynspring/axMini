#include "axMini/ExecutionEngine.hpp"

void ExecutionEngine::Execute(const std::vector<IfStatement> &statements) {
  for (const auto &statement : statements) {
    if (EvaluateCondition(statement.condition)) {
      var_engine_.WriteVariable(statement.assignment.variable,
                                statement.assignment.value);
    }
  }
}

/*IF motor_1.speed > 100 THEN valve_1.is_open = true; END_IF;*/
bool ExecutionEngine::EvaluateCondition(const Condition &cond) const {
  auto var = var_engine_.GetVariable(cond.left);
  if (!var.has_value()) {
    return false;
  }
  if (var->value.index() != cond.value.index()) {
    return false;
  }

  if (std::holds_alternative<int>(var->value)) {
    int left = std::get<int>(var->value);
    int right = std::get<int>(cond.value);
    switch (cond.comparison) {
    case ComparisonOp::kGreaterThan:
      return left > right;
    case ComparisonOp::kLessThan:
      return left < right;
    case ComparisonOp::kEqualEqual:
      return left == right;
    case ComparisonOp::kNotEqual:
      return left != right;
    default:
      return false;
    }
  } else if (std::holds_alternative<float>(var->value)) {
    float left = std::get<float>(var->value);
    float right = std::get<float>(cond.value);
    switch (cond.comparison) {
    case ComparisonOp::kGreaterThan:
      return left > right;
    case ComparisonOp::kLessThan:
      return left < right;
    case ComparisonOp::kEqualEqual:
      return left == right;
    case ComparisonOp::kNotEqual:
      return left != right;
    default:
      return false;
    }
  } else if (std::holds_alternative<bool>(var->value)) {
    bool left = std::get<bool>(var->value);
    bool right = std::get<bool>(cond.value);
    switch (cond.comparison) {
    case ComparisonOp::kEqualEqual:
      return left == right;
    case ComparisonOp::kNotEqual:
      return left != right;
    default:
      return false;
    }
  }
  return false;
}
