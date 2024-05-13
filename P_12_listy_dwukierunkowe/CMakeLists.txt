cmake_minimum_required(VERSION 3.24)
project(P_12_listy_dwukierunkowe C)

set(CMAKE_C_STANDARD 99)

add_executable(P_12_listy_dwukierunkowe main.c)
target_link_libraries(P_12_listy_dwukierunkowe m)
install(TARGETS P_12_listy_dwukierunkowe RUNTIME DESTINATION bin) 
