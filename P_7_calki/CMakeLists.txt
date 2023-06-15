cmake_minimum_required(VERSION 3.24)
project(P_7_calki C)

set(CMAKE_C_STANDARD 99)

add_executable(P_7_calki main.c)

install(TARGETS P_7_calki RUNTIME DESTINATION bin)