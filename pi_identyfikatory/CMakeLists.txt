cmake_minimum_required(VERSION 3.24)
project(pi_identyfikatory C)

set(CMAKE_C_STANDARD 99)

configure_file(test ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(test1 ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(test3 ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_executable(pi_identyfikatory main.c)

install(TARGETS pi_identyfikatory RUNTIME DESTINATION bin)