#pragma once

#include "ASTNode.hpp"
#include "Token.hpp"
#include <optional>
#include <variant>
#include <vector>

class Parser {
public:
  static std::vector<VarDeclaration> Parse(const std::vector<Token> &token);
  static std::vector<ObjectDeclaration>
  ParseObjectDeclarations(const std::vector<Token> &token);

private:
  static std::optional<std::variant<int, float, bool>>
  ParseValue(const Token &t);
};
