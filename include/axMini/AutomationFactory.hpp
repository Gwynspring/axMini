#pragma once

#include "axMini/ASTNode.hpp"
#include "axMini/AutomationObject.hpp"
#include "axMini/VariableEngine.hpp"
#include <memory>
#include <vector>

class AutomationFactory {
public:
  std::vector<std::unique_ptr<AutomationObject>>
  Create(const std::vector<ObjectDeclaration> &declarations,
         VariableEngine &var_engine);
};
