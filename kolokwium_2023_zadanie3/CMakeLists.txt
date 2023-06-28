cmake_minimum_required(VERSION 3.24)
project(kolokwium_2023_zadanie3 C)

set(CMAKE_C_STANDARD 99)

add_executable(kolokwium_2023_zadanie3 main.c)

install(TARGETS kolokwium_2023_zadanie3 RUNTIME DESTINATION bin)