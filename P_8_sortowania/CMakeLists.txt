cmake_minimum_required(VERSION 3.24)
project(P_8_sortowania C)

set(CMAKE_C_STANDARD 99)

add_executable(P_8_sortowania main.c)

install(TARGETS P_8_sortowania RUNTIME DESTINATION bin)

configure_file(foods0.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(foods.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(foods10.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)