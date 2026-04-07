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
