cmake_minimum_required(VERSION 3.24)
project(P_4_1_stringi C)

set(CMAKE_C_STANDARD 99)

configure_file( test1 ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file( test2 ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file( test3 ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file( test4 ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file( test5 ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file( test ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_executable(P_4_1_stringi main.c)

install(TARGETS P_4_1_stringi RUNTIME DESTINATION bin)