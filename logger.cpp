#include "logger.h"

const std::string_view RED = "\033[38;5;196m", ORANGE = "\033[38;5;220m", WHITE = "\033[38;5;252m", RESET = "\033[0m";
const std::string_view ERROR_LOG_PREFIX = "[ ERROR ] ", WARNING_LOG_PREFIX = "[WARNING] ", INFO_LOG_PREFIX = "[  LOG  ] ";
const std::string_view END_LINE = "\n", SEPARATOR = " - ";

template <typename T>
void Logger::LogError(T const& log_text){
    Logger::Log(LogLevel::ErrorLog, log_text);
}

template <typename T>
void Logger::LogWarning(T const& log_text){
    Logger::Log(LogLevel::WarningLog, log_text);
}

template <typename T>
void Logger::LogInfo(T const& log_text){
    Logger::Log(LogLevel::InfoLog, log_text);
}

void Logger::SetOutputFile(const std::string_view &outputFile) {
    _outputFile = outputFile;
}

template<typename T>
void Logger::WriteToConsole(const std::string_view &color, const std::string_view &prefix, const T &log_text) {
    std::cout << color << prefix << log_text << RESET << END_LINE;
}

template<typename T>
void Logger::Log(const char &level, const T &log_text) {

}
