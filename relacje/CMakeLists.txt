cmake_minimum_required(VERSION 3.24)
project(relacje C)

set(CMAKE_C_STANDARD 99)

add_executable(relacje main.c)

install(TARGETS relacje RUNTIME DESTINATION bin)