cmake_minimum_required (VERSION 3.25)

project(Ceb C)

# Set variables that can then be used by the parent project
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake" PARENT_SCOPE)
set(CEB_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}" PARENT_SCOPE)

add_executable(Ceb ceb.c ceb_gen.c ceb_base.c)

target_compile_definitions(Ceb PRIVATE CEB_BUILD)

include(TestBigEndian)
TEST_BIG_ENDIAN(IS_BIG_ENDIAN)
if(IS_BIG_ENDIAN)
  target_compile_definitions(Ceb PRIVATE CEB_BIG_ENDIAN)
endif()

