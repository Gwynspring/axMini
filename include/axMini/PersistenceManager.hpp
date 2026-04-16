#pragma once

#include "DslRuntime.hpp"
#include "VariableEngine.hpp"
#include <filesystem>

class PersistenceManager {
public:
  PersistenceManager(VariableEngine &var_engine, DslRuntime &runtime,
                     const std::string &filepath)
      : engine_(var_engine), runtime_(runtime),
        filepath_(std::filesystem::path(filepath)) {};

  bool Load();
  bool Save();

private:
  VariableEngine &engine_;
  DslRuntime &runtime_;
  std::filesystem::path filepath_;
};
