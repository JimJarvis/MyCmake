#cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
#set(CMAKE_LEGACY_CYGWIN_WIN32 0)
#project(MyCmake CXX)

message("GTest template")

# ==== GTest ====
set(TEST_SUITE mygtest)

add_gtest(${TEST_SUITE} ${TEST_SUITE}.cpp)
# so that you can run 'make gtest'
add_custom_target(gtest COMMAND ${TEST_SUITE})
