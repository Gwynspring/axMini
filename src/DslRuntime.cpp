#include "axMini/DslRuntime.hpp"

void DslRuntime::AddStatements(const std::vector<IfStatement> &statements) {
  std::lock_guard<std::mutex> lock(mutex_);
  statements_.insert(statements_.end(), statements.begin(), statements.end());
}

std::vector<IfStatement> DslRuntime::GetStatements() const {
  std::lock_guard<std::mutex> lock(mutex_);
  return statements_;
}

void DslRuntime::Clear() {
  std::lock_guard<std::mutex> lock(mutex_);
  statements_.clear();
}
