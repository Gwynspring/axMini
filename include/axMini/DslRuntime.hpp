#pragma once

#include "ASTNode.hpp"
#include <mutex>
#include <vector>

class DslRuntime {
public:
  DslRuntime() = default;

  void AddStatements(const std::vector<IfStatement> &statements);
  std::vector<IfStatement> GetStatements() const;
  void Clear();

private:
  std::vector<IfStatement> statements_;
  mutable std::mutex mutex_;
};
