#pragma once
#include <iostream>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

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