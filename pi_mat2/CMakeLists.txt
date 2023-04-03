cmake_minimum_required(VERSION 3.24)
project(pi_mat2 C)

set(CMAKE_C_STANDARD 99)

add_executable(pi_mat2 main.c)

install(TARGETS pi_mat2 RUNTIME DESTINATION bin)