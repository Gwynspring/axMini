#pragma once

class AutomationObject {
public:
  virtual void Update() = 0;
  virtual ~AutomationObject() = default;
};
