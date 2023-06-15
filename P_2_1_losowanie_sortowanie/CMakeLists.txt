cmake_minimum_required(VERSION 3.24)
project(P_2_1_losowanie_sortowanie C)

set(CMAKE_C_STANDARD 99)

add_executable(P_2_1_losowanie_sortowanie main.c)

install(TARGETS P_2_1_losowanie_sortowanie RUNTIME DESTINATION bin)