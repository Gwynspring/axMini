#include "axMini/AutomationFactory.hpp"
#include "axMini/Motor.hpp"
#include "axMini/Valve.hpp"
#include <memory>
#include <vector>

std::vector<std::unique_ptr<AutomationObject>>
AutomationFactory::Create(const std::vector<ObjectDeclaration> &declarations,
                          VariableEngine &var_engine) {

  std::vector<std::unique_ptr<AutomationObject>> objs;

  for (const auto &decl : declarations) {
    switch (decl.obj_type) {
    case ObjectType::kMotor: {
      auto obj = std::make_unique<Motor>(var_engine, decl.name);
      objs.push_back(std::move(obj));
      break;
    }

    case ObjectType::kValve: {
      auto obj = std::make_unique<Valve>(var_engine, decl.name);
      objs.push_back(std::move(obj));
      break;
    }
    default:
      __builtin_unreachable();
    }
  }
  return objs;
}
