cmake_minimum_required(VERSION 3.24)
project(sortowania C)

set(CMAKE_C_STANDARD 99)

add_executable(sortowania main.c)

install(TARGETS sortowania RUNTIME DESTINATION bin)

configure_file(foods0.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(foods.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(foods10.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)