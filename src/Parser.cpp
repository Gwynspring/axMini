#include "axMini/Parser.hpp"
#include "axMini/ASTNode.hpp"
#include "axMini/Types.hpp"
#include <vector>

std::vector<VarDeclaration> Parser::Parse(const std::vector<Token> &token) {
  std::vector<VarDeclaration> vd;

  for (size_t i = 0; i < token.size(); i++) {
    if (token.at(i).token_type != TokenType::kKeyWord)
      continue;
    if (i + 6 >= token.size())
      continue;
    if (token.at(i + 1).token_type != TokenType::kIdentifier)
      continue;
    if (token.at(i + 2).token_type != TokenType::kColon)
      continue;
    if (token.at(i + 3).token_type != TokenType::kType)
      continue;
    if (token.at(i + 4).token_type != TokenType::kEquals)
      continue;
    if (token.at(i + 5).token_type != TokenType::kIntValue &&
        token.at(i + 5).token_type != TokenType::kFloatValue &&
        token.at(i + 5).token_type != TokenType::kBoolValue)
      continue;
    if (token.at(i + 6).token_type != TokenType::kEndOfStatement)
      continue;

    auto data_type = DataTypeFromString(token.at(i + 3).value);
    if (!data_type.has_value())
      continue;

    auto value = ParseValue(token.at(i + 5));
    if (!value.has_value())
      continue;

    vd.push_back(VarDeclaration(token.at(i + 1).value, data_type.value(),
                                value.value()));

    i += 6;
  }
  return vd;
}

std::vector<ObjectDeclaration>
Parser::ParseObjectDeclarations(const std::vector<Token> &token) {
  std::vector<ObjectDeclaration> od;

  for (size_t i = 0; i < token.size(); i++) {
    if (token.at(i).token_type != TokenType::kObjectKeyWord)
      continue;
    if (i + 2 >= token.size())
      continue;
    if (token.at(i + 1).token_type != TokenType::kIdentifier)
      continue;
    if (token.at(i + 2).token_type != TokenType::kEndOfStatement)
      continue;

    auto obj_type = ObjectTypeFromString(token.at(i).value);
    if (!obj_type.has_value())
      continue;

    od.push_back(ObjectDeclaration(token.at(i + 1).value, obj_type.value()));

    i += 2;
  }
  return od;
}

/*
0. kIfKeyword
1. kIdentifier       ← condition.left
2. kGreaterThan      ← ComparisonOp
3. kIntValue         ← condition.value
4. kThenKeyword
5. kIdentifier       ← assignment.variable
6. kEquals
7. kBoolValue        ← assignment.value
8. kEndOfStatement
9. kEndIfKeyword
10. kEndOfStatement
*/

std::vector<IfStatement>
Parser::ParseIfStatement(const std::vector<Token> &token) {

  std::vector<IfStatement> if_statements;
  for (size_t i = 0; i < token.size(); i++) {
    if (token.at(i).token_type != TokenType::kIfKeyword) {
      continue;
    }
    if (i + 10 >= token.size()) {
      continue;
    }
    if (token.at(i + 1).token_type != TokenType::kIdentifier) {
      continue;
    }
    if (token.at(i + 2).token_type != TokenType::kGreaterThan &&
        token.at(i + 2).token_type != TokenType::kLessThan &&
        token.at(i + 2).token_type != TokenType::kEqualEqual &&
        token.at(i + 2).token_type != TokenType::kNotEqual &&
        token.at(i + 2).token_type != TokenType::kAnd &&
        token.at(i + 2).token_type != TokenType::kOr) {
      continue;
    }
    if (token.at(i + 3).token_type != TokenType::kIntValue &&
        token.at(i + 3).token_type != TokenType::kFloatValue &&
        token.at(i + 3).token_type != TokenType::kBoolValue) {
      continue;
    }
    if (token.at(i + 4).token_type != TokenType::kThenKeyword) {
      continue;
    }
    if (token.at(i + 5).token_type != TokenType::kIdentifier) {
      continue;
    }
    if (token.at(i + 6).token_type != TokenType::kEquals) {
      continue;
    }
    if (token.at(i + 7).token_type != TokenType::kIntValue &&
        token.at(i + 7).token_type != TokenType::kFloatValue &&
        token.at(i + 7).token_type != TokenType::kBoolValue) {
      continue;
    }
    if (token.at(i + 8).token_type != TokenType::kEndOfStatement) {
      continue;
    }
    if (token.at(i + 9).token_type != TokenType::kEndIfKeyword) {
      continue;
    }
    if (token.at(i + 10).token_type != TokenType::kEndOfStatement) {
      continue;
    }

    auto comp_op = ComparisonOpFromTokenType(token.at(i + 2).token_type);
    if (!comp_op.has_value())
      continue;

    auto value = ParseValue(token.at(i + 3));
    if (!value.has_value())
      continue;

    Condition cond(token.at(i + 1).value, comp_op.value(), value.value());

    value = ParseValue(token.at(i + 7));
    if (!value.has_value())
      continue;

    Assignment assignment(token.at(i + 5).value, value.value());
    if_statements.push_back(IfStatement(cond, assignment));
    i += 10;
  }
  return if_statements;
}

std::optional<std::variant<int, float, bool>>
Parser::ParseValue(const Token &t) {
  switch (t.token_type) {
  case TokenType::kIntValue:
    return std::stoi(t.value);
  case TokenType::kFloatValue:
    return std::stof(t.value);
  case TokenType::kBoolValue:
    if (t.value == "true") {
      return true;
    } else {
      return false;
    }
  default:
    return std::nullopt;
  }
}
