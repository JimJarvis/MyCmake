message("Folder test/ for gtest template")
include(eona_gtest)

set(TEST_SUITE mygtest)

add_gtest(${TEST_SUITE} ${TEST_SUITE}.cpp)

# so that you can run 'make gtest'
add_custom_target(gtest COMMAND ${TEST_SUITE})
