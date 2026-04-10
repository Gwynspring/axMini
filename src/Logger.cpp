#include "axMini/Logger.hpp"

#include "spdlog/async.h"
#include "spdlog/logger.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

std::shared_ptr<spdlog::logger> Logger::logger_ = nullptr;

void Logger::Init() {
  spdlog::init_thread_pool(8192, 1);
  auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
  auto rotating_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
      "axMini.log", 1024 * 1024 * 10, 3);
  std::vector<spdlog::sink_ptr> sinks{stdout_sink, rotating_sink};
  logger_ = std::make_shared<spdlog::async_logger>(
      "axLogger", sinks.begin(), sinks.end(), spdlog::thread_pool(),
      spdlog::async_overflow_policy::block);
  spdlog::register_logger(logger_);
}

void Logger::Info(const std::string &msg) { logger_->info(msg); }
void Logger::Warn(const std::string &msg) { logger_->warn(msg); }
void Logger::Error(const std::string &msg) { logger_->error(msg); }
