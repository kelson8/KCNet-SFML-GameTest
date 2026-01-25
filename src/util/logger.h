#pragma once
#include "defines.h"
#include <iostream>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>


// Toggle the fmt format logger, this can be disabled in Release builds.
#ifdef ENABLE_LOGGING
#define FMT_LOG(...) fmt::println(__VA_ARGS__)
#else
#define FMT_LOG(fmt, ...) // No-op
#endif // ENABLE_LOGGING

enum class LogLevel {
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_CRITICAL,
    LOG_DEBUG,
    LOG_TRACE,
};

class Logger
{
public:

    static Logger& getInstance()
    {
        static Logger instance; // Guaranteed to be destroyed.
        return instance;
    }

    void Log(LogLevel logLevel, const std::string& text);

private:
    Logger();
    // ~Logger();

    std::shared_ptr<spdlog::logger> filelog;

    Logger(const Logger&) = delete;            // Prevent copy-construction
    Logger& operator=(const Logger&) = delete; // Prevent assignment

};