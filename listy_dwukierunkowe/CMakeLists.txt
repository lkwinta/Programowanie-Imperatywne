cmake_minimum_required(VERSION 3.24)
project(listy_dwukierunkowe C)

set(CMAKE_C_STANDARD 99)

add_executable(listy_dwukierunkowe main.c)
target_link_libraries(listy_dwukierunkowe m)
install(TARGETS listy_dwukierunkowe RUNTIME DESTINATION bin)