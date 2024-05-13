cmake_minimum_required(VERSION 3.24)
project(P_2_2_stos_kolejka C)

set(CMAKE_C_STANDARD 99)

add_executable(P_2_2_stos_kolejka main.c)

install(TARGETS P_2_2_stos_kolejka RUNTIME DESTINATION bin) 
