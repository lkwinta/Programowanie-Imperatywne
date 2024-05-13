cmake_minimum_required(VERSION 3.24)
project(P_9_tablice_2d C)

set(CMAKE_C_STANDARD 99)

add_executable(P_9_tablice_2d main.c)

install(TARGETS P_9_tablice_2d RUNTIME DESTINATION bin)

configure_file(test2 ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(test3 ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(test4 ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(test5 ${CMAKE_CURRENT_BINARY_DIR} COPYONLY) 
