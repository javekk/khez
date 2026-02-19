#pragma once

#include <string>

enum LogLevel {
    DEBUG,
    INFO,
    WARN,
    ERROR,
};

struct LoggerProps {
    LogLevel minLevel = LogLevel::DEBUG;
    bool enableTimestamp = true;
    bool enabled = true;
};

class Logger {
   public:
    // Disable copy and assigment
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    static void configure(const LoggerProps& props) {
        getInstance().props_ = props;
    }

    void log(LogLevel level, const std::string& message) const;

    void debug(const std::string& message) const;
    void info(const std::string& message) const;
    void warn(const std::string& message) const;
    void error(const std::string& message) const;

   private:
    LoggerProps props_;
    Logger() = default;
};

inline Logger& logger = Logger::getInstance();