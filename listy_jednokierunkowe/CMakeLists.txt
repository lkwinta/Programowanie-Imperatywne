cmake_minimum_required(VERSION 3.24)
project(listy_jednokierunkowe C)

set(CMAKE_C_STANDARD 99)

add_executable(listy_jednokierunkowe main.c)

install(TARGETS listy_jednokierunkowe RUNTIME DESTINATION bin)