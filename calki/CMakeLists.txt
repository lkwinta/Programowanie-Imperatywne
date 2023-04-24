cmake_minimum_required(VERSION 3.24)
project(calki C)

set(CMAKE_C_STANDARD 99)

add_executable(calki main.c)

install(TARGETS calki RUNTIME DESTINATION bin)