#ifndef LOGGER_LOGGER_H
#define LOGGER_LOGGER_H

#include <iostream>
#include <string>
#include <string_view>
#include <filesystem>
#include <ctime>
#include <sstream>
#include <fstream>

class Logger {
    inline static const std::string_view RED = "\033[38;5;196m", ORANGE = "\033[38;5;220m", WHITE = "\033[38;5;252m", RESET = "\033[0m";
    inline static const std::string_view ERROR_LOG_PREFIX = "[ ERROR ] ", WARNING_LOG_PREFIX = "[WARNING] ", INFO_LOG_PREFIX = "[  LOG  ] ";
    inline static const std::string_view END_LINE = "\n", SEPARATOR = " - ";

    enum class LogLevel : char {
        ErrorLog, WarningLog, InfoLog
    };

    inline static std::string _outputFile;
    inline static bool _logTime = true;

    static std::string GetLocalTime() {
        std::time_t t = std::time(nullptr);
        std::stringstream ss;
        ss << std::put_time(localtime(&t), "%H:%M:%S %d/%m/%Y");
        return ss.str();
    }

    template<typename T>
    static void Log(const Logger::LogLevel &logLevel, T const &log_text) {
        std::string_view prefix, color, separator;
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
        std::string timeAndDate;
        if(_logTime) {
            timeAndDate = GetLocalTime();
            separator = SEPARATOR;
        }
        std::stringstream log_message;
        log_message << prefix << timeAndDate << separator << log_text;
        WriteToConsole(color, log_message.str());
        if (!_outputFile.empty())
            WriteToFile(log_message.str());
    }

    static void WriteToConsole(const std::string_view &color, const std::string_view &log_message) {
        std::cout << color << log_message << RESET << END_LINE;
    }

    static void WriteToFile(const std::string_view &log_message) {
        std::ofstream writeFile(_outputFile, std::ios::app);
        if(!writeFile || !writeFile.is_open()){
            LogError("Logger could not save to file");
            _outputFile = "";
            return;
        }
        writeFile << log_message << END_LINE;
        writeFile.close();
    }

public:
    Logger() = delete;

    ~Logger() = delete;

    Logger operator=(const Logger& logger) = delete;

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

    static void EnableTimeLogging(){
        _logTime = true;
    }

    static void DisableTimeLogging(){
        _logTime = false;
    }

    static bool isLoggingTime(){
        return _logTime;
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
