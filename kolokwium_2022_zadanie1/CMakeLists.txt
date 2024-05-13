cmake_minimum_required(VERSION 3.24)
project(kolokwium_2022_zadanie1 C)

set(CMAKE_C_STANDARD 99)

add_executable(kolokwium_2022_zadanie1 main.c)

install(TARGETS kolokwium_2022_zadanie1 RUNTIME DESTINATION bin) 
