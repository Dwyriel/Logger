cmake_minimum_required(VERSION 3.24)
project(Logger)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(Logger logger.cpp)

add_executable(Exec main.cpp)