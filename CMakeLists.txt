cmake_minimum_required (VERSION 3.25)

project(Ceb C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-g")

add_executable(Ceb ceb.c ceb_gen.c)
