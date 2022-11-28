#ifndef LOGGER_LOGGER_H
#define LOGGER_LOGGER_H

#include <iostream>
#include <string>
#include <string_view>

class Logger {
    enum class LogLevel : char {ErrorLog, WarningLog, InfoLog};

    static std::string _outputFile;

    template <typename T>
    static void Log(const char& level, T const& log_text);

    template <typename T>
    static void WriteToConsole(const std::string_view& color, const std::string_view& prefix, T const& log_text);

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
    static void SetOutputFile(const std::string_view &outputFile = "");

    template <typename T>
    static void LogError(T const& log_text);

    template <typename T>
    static void LogWarning(T const& log_text);

    template <typename T>
    static void LogInfo(T const& log_text);
};

#endif //LOGGER_LOGGER_H
