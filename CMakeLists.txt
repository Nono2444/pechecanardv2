cmake_minimum_required(VERSION 3.23)
project(pecheauxcanards C)

set(CMAKE_C_STANDARD 99)

add_executable(pecheauxcanards main.c)
target_link_libraries(pecheauxcanards -lmingw32 -lalleg44)
