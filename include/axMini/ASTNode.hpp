#pragma once

#include "Types.hpp"
#include <string>
#include <utility>
#include <variant>

struct VarDeclaration {
  std::string name;
  DataType type;
  std::variant<int, float, bool> initial_value;
  VarDeclaration(std::string n, DataType t, std::variant<int, float, bool> val)
      : name(std::move(n)), type(t), initial_value(std::move(val)) {};
};

struct ObjectDeclaration {
  std::string name;
  ObjectType obj_type;
  ObjectDeclaration(std::string n, ObjectType t)
      : name(std::move(n)), obj_type(t) {};
};

struct Condition {
  std::string left;
  ComparisonOp comparison;
  std::variant<int, float, bool> value;
  Condition(std::string l, ComparisonOp comp_op,
            std::variant<int, float, bool> val)
      : left(std::move(l)), comparison(comp_op), value(std::move(val)) {};
};

struct Assignment {
  std::string variable;
  std::variant<int, float, bool> value;
  Assignment(std::string var, std::variant<int, float, bool> val)
      : variable(std::move(var)), value(std::move(val)) {};
};

struct IfStatement {
  Condition condition;
  Assignment assignment;
  IfStatement(Condition cond, Assignment ass)
      : condition(std::move(cond)), assignment(std::move(ass)) {};
};
