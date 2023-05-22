cmake_minimum_required(VERSION 3.24)
project(uogolnione_wektory C)

set(CMAKE_C_STANDARD 99)

add_executable(uogolnione_wektory main.c)

install(TARGETS uogolnione_wektory RUNTIME DESTINATION bin)