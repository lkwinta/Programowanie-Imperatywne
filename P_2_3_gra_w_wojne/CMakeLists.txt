cmake_minimum_required(VERSION 3.24)
project(P_2_3_gra_w_wojne C)

set(CMAKE_C_STANDARD 99)

add_executable(P_2_3_gra_w_wojne main.c helper.c)

install(TARGETS P_2_3_gra_w_wojne RUNTIME DESTINATION bin)