cmake_minimum_required(VERSION 3.24)
project(P_11_listy_jednokierunkowe C)

set(CMAKE_C_STANDARD 99)

add_executable(P_11_listy_jednokierunkowe main.c)

install(TARGETS P_11_listy_jednokierunkowe RUNTIME DESTINATION bin)

configure_file(Tekst_1.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(Tekst_C.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)