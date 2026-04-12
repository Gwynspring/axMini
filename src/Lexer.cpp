#include "axMini/Lexer.hpp"
#include "axMini/Token.hpp"
#include <string>

bool Lexer::IsNumber(const std::string &s) {
  std::string::const_iterator it = s.begin();
  while (it != s.end() && std::isdigit(*it))
    ++it;
  return !s.empty() && it == s.end();
}

std::vector<Token> Lexer::Tokenize(const std::string &input) {
  std::vector<Token> token;

  for (size_t i = 0; i < input.length(); i++) {
    if (input[i] == ' ' || input[i] == '\t' || input[i] == '\r' ||
        input[i] == '\n') {
      continue;
    }
    switch (input[i]) {
    case ':':
      token.push_back(Token(TokenType::kColon, ":"));
      break;

    case '!':
      if (i + 1 < input.length() && input[i + 1] == '=') {
        token.push_back(Token(TokenType::kNotEqual, "!="));
        i++;
        break;
      } else
        break;

    case '>':
      token.push_back(Token(TokenType::kGreaterThan, ">"));
      break;
    case '<':
      token.push_back(Token(TokenType::kLessThan, "<"));
      break;

    case '&':
      if (i + 1 <= input.length() && input[i + 1] == '&') {
        token.push_back(Token(TokenType::kAnd, "&&"));
        i++;
        break;
      } else
        break;

    case '|':
      if (i + 1 <= input.length() && input[i + 1] == '|') {
        token.push_back(Token(TokenType::kOr, "||"));
        i++;
        break;
      } else
        break;

    case '=':
      if (i + 1 < input.length() && input[i + 1] == '=') {
        token.push_back(Token(TokenType::kEqualEqual, "=="));
        i++;
        break;
      }
      token.push_back(Token(TokenType::kEquals, "="));
      break;

    case ';':
      token.push_back(Token(TokenType::kEndOfStatement, ";"));
      break;

    default:
      size_t counter = 0;
      std::string word;
      while ((i + counter < input.length()) && input[i + counter] != ' ' &&
             input[i + counter] != ';' && input[i + counter] != ':' &&
             input[i + counter] != '=' && input[i + counter] != '<' &&
             input[i + counter] != '>' && input[i + counter] != '!') {
        word += input[i + counter];
        counter++;
      }
      i += counter - 1;

      if (word == "VAR") {
        token.push_back(Token(TokenType::kKeyWord, "VAR"));
      } else if (word == "MOTOR" || word == "VALVE") {
        token.push_back(Token(TokenType::kObjectKeyWord, word));
      } else if (word == "INT" || word == "FLOAT" || word == "BOOL") {
        token.push_back(Token(TokenType::kType, word));
      } else if (word == "IF") {
        token.push_back(Token(TokenType::kIfKeyword, "IF"));
      } else if (word == "THEN") {
        token.push_back(Token(TokenType::kThenKeyword, "THEN"));
      } else if (word == "END_IF") {
        token.push_back(Token(TokenType::kEndIfKeyword, "END_IF"));
      } else {
        if (word == "true" || word == "false") {
          token.push_back(Token(TokenType::kBoolValue, word));
        } else if (word.find('.') != std::string::npos) {
          token.push_back(Token(TokenType::kFloatValue, word));
        } else if (IsNumber(word)) {
          token.push_back(Token(TokenType::kIntValue, word));
        } else {
          token.push_back(Token(TokenType::kIdentifier, word));
        }
      }
      break;
    }
  }
  return token;
}
