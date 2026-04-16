#include "axMini/DslRuntime.hpp"

void DslRuntime::AddStatements(const std::vector<IfStatement> &statements,
                               const std::string &dsl_str) {
  std::lock_guard<std::mutex> lock(mutex_);
  statements_.insert(statements_.end(), statements.begin(), statements.end());
  if (!dsl_str.empty()) {
    dsl_strings_.push_back(dsl_str);
  }
}

std::vector<IfStatement> DslRuntime::GetStatements() const {
  std::lock_guard<std::mutex> lock(mutex_);
  return statements_;
}

std::vector<std::string> DslRuntime::GetDslStrings() const {
  std::lock_guard<std::mutex> lock(mutex_);
  return dsl_strings_;
}

void DslRuntime::Clear() {
  std::lock_guard<std::mutex> lock(mutex_);
  statements_.clear();
  dsl_strings_.clear();
}
