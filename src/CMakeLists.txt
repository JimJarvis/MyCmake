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

set(MAIN
    main)

set(SOURCES 
    ${MAIN}.cpp)

add_definitions(-std=c++11 -pthread)

add_thread(${MAIN} ${SOURCES})

# ==== boost ====
include(eona_boost)

link_boost(${MAIN} ${Boost_LIBRARIES})
# for boost testing ONLY
add_boost(boosttest boosttest.cpp)

# ==== more libs ====
option (USE_MYLIB "Use my optional lib" OFF)

if (USE_MYLIB)
    include_directories("${PROJECT_BINARY_DIR}")
    add_subdirectory(MyLib)
    set (EXTRA_LIBS ${EXTRA_LIBS} MyLib)
endif()

# ==== installation ====
option (MY_INSTALLER OFF)
if (MY_INSTALLER)
    install(TARGETS main DESTINATION ${PROJECT_BINARY_DIR})
endif()

# ==== GTest ====
include(eona_gtest)
#set(TEST_SUITE mygtest)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../test/ ${CMAKE_CURRENT_BINARY_DIR}/test)
#add_gtest(${TEST_SUITE} ${TEST_SUITE}.cpp)
# so that you can run 'make gtest'
#add_custom_target(gtest COMMAND ${TEST_SUITE})

# ==== CTest (cmake default) ====
include(eona_ctest)
