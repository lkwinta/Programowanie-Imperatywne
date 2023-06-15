cmake_minimum_required(VERSION 3.24)
project(P_5_1_macierze_1 C)

set(CMAKE_C_STANDARD 99)

add_executable(P_5_1_macierze_1 main.c)

install(TARGETS P_5_1_macierze_1 RUNTIME DESTINATION bin)