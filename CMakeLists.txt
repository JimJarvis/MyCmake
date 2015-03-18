cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)
project(MyCmake CXX)

message("Welcome to Jim's template")

# you can isolate CMake code out by adding a new dir to your src, and add a
# new file MyXXX.cmake:
# list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
# include(myXXX)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(eona_utils)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test 
    ${CMAKE_CURRENT_BINARY_DIR}/test)
