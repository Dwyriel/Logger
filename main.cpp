#include "logger.h"
int main(int argc, char *argv[], char* envp[]){


    Logger::LogInfo("Info");
    Logger::LogWarning("Warning");
    Logger::LogError("Error");

    Logger::SetOutputFile(std::string(argv[0]) + ".txt");

}