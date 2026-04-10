#pragma once

#include "spdlog/spdlog.h"
#include <memory>
#include <string>

class Logger {
public:
  static void Init();
  static void Info(const std::string &msg);
  static void Warn(const std::string &msg);
  static void Error(const std::string &msg);

private:
  static std::shared_ptr<spdlog::logger> logger_;
};
