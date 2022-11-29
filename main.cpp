#include "logger.h"

int main(int argc, char *argv[], char* envp[]){
    Logger::LogInfo("Info");
    Logger::LogError("Error");
    Logger::LogWarning("Warning");

    Logger::SetOutputFile(std::string(argv[0]) + ".txt");

    Logger::SetOutputFile("/home/dwyriel/Code/CPP/count_primes/bin");
    Logger::SetOutputFile("/home/dwyriel/Code/CPP/Logger/cmake-build-debug/texty.txt");

    Logger::SetOutputFile("/home/dwyriel/Code/CPP/Logger/cmake-build-debug/a/b/c/texty.txt");


    Logger::SetOutputFile("/home/dwyriel/Code/CPP/Logger/cmake-build-debug/weee/");
    Logger::SetOutputFile("/home/dwyriel/Code/CPP/Logger/cmake-build-debug/tsx.conf");


}