#include "logger.h"

#include <ctime>
#include <iostream>
#include <sstream>

void Logger::debug(const std::string& message) const { log(DEBUG, message); }
void Logger::info(const std::string& message) const { log(INFO, message); }
void Logger::warn(const std::string& message) const { log(WARN, message); }
void Logger::error(const std::string& message) const { log(ERROR, message); }

std::string levelToString(LogLevel level) {
    std::string RED = "\x1B[31m";
    std::string YELLOW = "\x1B[33m";
    std::string BLUE = "\x1B[34m";
    std::string GREEN = "\x1B[32m";

    std::string END = "\033[0m";

    switch (level) {
        case DEBUG:
            return "[" + BLUE + "DEBUG" + END + "] ";
        case INFO:
            return "[" + GREEN + "INFO" + END + "] ";
        case WARN:
            return "[" + YELLOW + "WARN" + END + "] ";
        case ERROR:
            return "[" + GREEN + "INFO" + END + "] ";
        default:
            return "UNKNOWN";
    }
}

void Logger::log(const LogLevel level, const std::string& message) const {
    std::ostringstream oss;

    if (props_.enableTimestamp) {
        time_t timestamp;
        time(&timestamp);
        std::string tsStr = ctime(&timestamp);
        tsStr.pop_back();

        oss << "[" << tsStr << "] ";
    }

    oss << levelToString(level);

    oss << message;

    std::cout << oss.str() << "\n";
}