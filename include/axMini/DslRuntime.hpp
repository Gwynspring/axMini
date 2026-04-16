#pragma once

#include "ASTNode.hpp"
#include <mutex>
#include <vector>

class DslRuntime {
public:
  DslRuntime() = default;

  void AddStatements(const std::vector<IfStatement> &statements,
                     const std::string &dsl_string = "");
  std::vector<IfStatement> GetStatements() const;
  void Clear();
  std::vector<std::string> GetDslStrings() const;

private:
  std::vector<IfStatement> statements_;
  std::vector<std::string> dsl_strings_;
  mutable std::mutex mutex_;
};
