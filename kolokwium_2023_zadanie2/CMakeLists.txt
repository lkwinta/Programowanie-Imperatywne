cmake_minimum_required(VERSION 3.24)
project(kolokwium_2023_zadanie2 C)

set(CMAKE_C_STANDARD 99)

add_executable(kolokwium_2023_zadanie2 main.c)

install(TARGETS kolokwium_2023_zadanie2 RUNTIME DESTINATION bin) 
