cmake_minimum_required(VERSION 3.24)
project(P_10_uogolnione_wektory C)

set(CMAKE_C_STANDARD 99)

add_executable(P_10_uogolnione_wektory main.c)

install(TARGETS P_10_uogolnione_wektory RUNTIME DESTINATION bin)