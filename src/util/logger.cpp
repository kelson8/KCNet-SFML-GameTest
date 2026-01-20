#include "logger.h"

#include <fstream>

#include "defines.h"

// Logger originally created for KCNet-NCurses
// This uses spdlog.

//------
// Log functions
//------

/**
 * @brief Initialize the logger with the log prefix and the log file.
 */
Logger::Logger()
{
    filelog = spdlog::basic_logger_mt(Defines::loggerPrefix, Defines::logFileName);
}

/**
 * @brief Basic function to log to a file, this uses the spdlog library.
 *
 * @param logLevel - The type of log to set, such as LogError::INFO, LogError::WARNING, LogLevel::ERROR.
 * @param textToLog - The text to log to the file.
 */
void Logger::Log(LogLevel logLevel, const std::string& text)
{
    // Set the logger format if needed.
    // filelog->set_pattern("[" + logPrefix + "] %v");

    // This can print out the contents of the log to the screen.
    // spdlog::info(textToLog);

    // Log the text to the file.

    switch (logLevel)
    {
    case LogLevel::LOG_INFO:
        filelog.get()->info(text);
        break;
    case LogLevel::LOG_WARNING:
        filelog.get()->warn(text);
        break;
    case LogLevel::LOG_ERROR:
        filelog.get()->error(text);
        break;

    case LogLevel::LOG_CRITICAL:
        filelog.get()->critical(text);
        break;
    case LogLevel::LOG_DEBUG:
        filelog.get()->debug(text);
        break;
    case LogLevel::LOG_TRACE:
        filelog.get()->trace(text);
        break;
    default:
        break;
    }

    // Flush the logger's buffer after logging
    filelog->flush();

    // filelog->flush_on();
}

/**
 * @brief Test for the logger system with macros, this is not currently in use.
 * 
 * https://github.com/gabime/spdlog/wiki/FAQ
 * 
 * https://stackoverflow.com/questions/45621996/how-to-enable-disable-spdlog-logging-in-code
 */
void TestLogger()
{

    // enable/disable log calls at compile time according to global level.
    //
    // define SPDLOG_ACTIVE_LEVEL to one of those (before including spdlog.h):
    // SPDLOG_LEVEL_TRACE,
    // SPDLOG_LEVEL_DEBUG,
    // SPDLOG_LEVEL_INFO,
    // SPDLOG_LEVEL_WARN,
    // SPDLOG_LEVEL_ERROR,
    // SPDLOG_LEVEL_CRITICAL,
    // SPDLOG_LEVEL_OFF
    //

    //spdlog::default_logger_raw();

    SPDLOG_TRACE("");
    SPDLOG_DEBUG("");
    SPDLOG_CRITICAL("");
    SPDLOG_ERROR("");
    SPDLOG_WARN("");
    SPDLOG_INFO("");

}
//