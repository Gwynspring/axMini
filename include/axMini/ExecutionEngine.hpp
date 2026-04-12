#pragma once

#include "ASTNode.hpp"
#include "VariableEngine.hpp"

class ExecutionEngine {
public:
  ExecutionEngine(VariableEngine &engine) : var_engine_(engine) {};
  void Execute(const std::vector<IfStatement> &statements);

private:
  VariableEngine &var_engine_;
  bool EvaluateCondition(const Condition &cond) const;
};
