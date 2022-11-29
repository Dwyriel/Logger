#ifndef LOGGER_LOGGER_H
#define LOGGER_LOGGER_H

#include <iostream>
#include <string>
#include <string_view>
#include <filesystem>

class Logger {
    inline static const std::string_view RED = "\033[38;5;196m", ORANGE = "\033[38;5;220m", WHITE = "\033[38;5;252m", RESET = "\033[0m";
    inline static const std::string_view ERROR_LOG_PREFIX = "[ ERROR ] ", WARNING_LOG_PREFIX = "[WARNING] ", INFO_LOG_PREFIX = "[  LOG  ] ";
    inline static const std::string_view END_LINE = "\n", SEPARATOR = " - ";

    enum class LogLevel : char {
        ErrorLog, WarningLog, InfoLog
    };

    inline static std::string _outputFile;

    template<typename T>
    static void Log(const Logger::LogLevel &logLevel, T const &log_text) {
        std::string_view prefix, color;
        switch (logLevel) {
            case LogLevel::ErrorLog:
                color = RED;
                prefix = ERROR_LOG_PREFIX;
                break;
            case LogLevel::WarningLog:
                color = ORANGE;
                prefix = WARNING_LOG_PREFIX;
                break;
            case LogLevel::InfoLog:
                color = WHITE;
                prefix = INFO_LOG_PREFIX;
                break;
            default:
                return;
        }
        WriteToConsole(color, prefix, log_text);
        if (_outputFile.empty())
            return;
        WriteToFile();
    }

    template<typename T>
    static void WriteToConsole(const std::string_view &color, const std::string_view &prefix, T const &log_text) {
        std::cout << color << prefix << log_text << RESET << END_LINE;
    }

    static void WriteToFile() {}//todo writing to a file;

public:
    Logger() = delete;

    ~Logger() = delete;

    /**
     * <br>Sets the output file full path.<br><br>
     * If output file is set and is valid, logging to file will automatically be done.<br>
     * Set to an empty string to not save logs to file. (Calling this function without passing anything will have this effect)<br><br>
     * Examples:
     * <br> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; SetOutputFile(std::string(args[0]) + "/log.txt");
     * <br> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; SetOutputFile(); //Resets the output file
     * @param outputFile Full file path.
     */
    static void SetOutputFile(const std::string_view &outputFile = "") {
        _outputFile = "";
        if (std::filesystem::exists(outputFile)) {
            if (std::filesystem::is_regular_file(outputFile))
                _outputFile = outputFile;
            return;
        }
        std::filesystem::path outputFilePath(outputFile);
        if (outputFilePath.filename().empty())
            return;
        outputFilePath.remove_filename();
        std::filesystem::create_directories(outputFilePath);
        _outputFile = outputFile;
    }

    static std::string_view GetOutputFile() noexcept {
        return _outputFile;
    }

    template<typename T>
    static void LogError(T const &log_text) {
        Logger::Log(LogLevel::ErrorLog, log_text);
    }

    template<typename T>
    static void LogWarning(T const &log_text) {
        Logger::Log(LogLevel::WarningLog, log_text);
    }

    template<typename T>
    static void LogInfo(T const &log_text) {
        Logger::Log(LogLevel::InfoLog, log_text);
    }
};

#endif //LOGGER_LOGGER_H
