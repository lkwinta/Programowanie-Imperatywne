cmake_minimum_required(VERSION 3.24)
project(P_3_statystyka C)

set(CMAKE_C_STANDARD 99)

add_executable(P_3_statystyka main.c)

install(TARGETS P_3_statystyka RUNTIME DESTINATION bin)