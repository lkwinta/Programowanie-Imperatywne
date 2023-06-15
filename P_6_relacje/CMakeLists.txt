cmake_minimum_required(VERSION 3.24)
project(P_6_relacje C)

set(CMAKE_C_STANDARD 99)

add_executable(P_6_relacje main.c)

install(TARGETS P_6_relacje RUNTIME DESTINATION bin)