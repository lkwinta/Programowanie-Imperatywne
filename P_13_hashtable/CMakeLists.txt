cmake_minimum_required(VERSION 3.24)
project(P_13_hashtable C)

set(CMAKE_C_STANDARD 99)

add_executable(P_13_hashtable main.c)
target_link_libraries(P_13_hashtable m)

install(TARGETS P_13_hashtable RUNTIME DESTINATION bin)

configure_file(test3 ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)