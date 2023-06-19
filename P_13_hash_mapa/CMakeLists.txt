cmake_minimum_required(VERSION 3.24)
project(P_13_hash_mapa C)

set(CMAKE_C_STANDARD 99)

add_executable(P_13_hash_mapa main.c)
target_link_libraries(P_13_hash_mapa m)

install(TARGETS P_13_hash_mapa RUNTIME DESTINATION bin)

configure_file(test3 ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)