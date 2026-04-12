#pragma once

#include "ASTNode.hpp"
#include "AutomationObject.hpp"
#include "VariableEngine.hpp"
#include <memory>
#include <vector>

class AutomationFactory {
public:
  std::vector<std::unique_ptr<AutomationObject>>
  Create(const std::vector<ObjectDeclaration> &declarations,
         VariableEngine &var_engine);
};
