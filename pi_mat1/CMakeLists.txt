cmake_minimum_required(VERSION 3.24)
project(pi_mat1 C)

set(CMAKE_C_STANDARD 99)

add_executable(pi_mat1 main.c)

install(TARGETS pi_mat1 RUNTIME DESTINATION bin)