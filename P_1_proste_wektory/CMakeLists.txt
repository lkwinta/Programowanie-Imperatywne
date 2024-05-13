cmake_minimum_required(VERSION 3.24)
project(P_1_proste_wektory C)

set(CMAKE_C_STANDARD 99)

add_executable(P_1_proste_wektory main.c)

install(TARGETS P_1_proste_wektory RUNTIME DESTINATION bin) 
