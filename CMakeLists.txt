cmake_minimum_required (VERSION 3.25)

project(Ceb C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

add_executable(Ceb ceb.c ceb_gen.c ceb_base.c)
