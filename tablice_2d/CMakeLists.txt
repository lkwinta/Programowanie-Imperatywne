cmake_minimum_required(VERSION 3.24)
project(tablice_2d C)

set(CMAKE_C_STANDARD 99)

add_executable(tablice_2d main.c)

install(TARGETS tablice_2d RUNTIME DESTINATION bin)