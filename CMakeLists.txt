cmake_minimum_required(VERSION 3.0)
project(sqlite_clone)

include_directories(./src)

add_executable(binary ./src/main.cpp ./src/repl.cpp)
