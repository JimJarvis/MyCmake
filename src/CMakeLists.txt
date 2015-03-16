cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)
project(MyCmake CXX)

message("Welcome to my fking template")

set(MAIN
    main)

set(SOURCES 
    ${MAIN}.cpp)

add_executable(${MAIN} ${SOURCES})
add_definitions(-std=c++11 -pthread)

#find_package(Threads REQUIRED)
#target_link_libraries(${MAIN} ${CMAKE_THREAD_LIBS_INIT})

set(CMAKE_EXE_LINKER_FLAGS "-pthread")

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

# ==== testing ====
enable_testing()

set(idx 0)
macro (Tester arg result)
    MATH(EXPR idx "${idx} + 1") 
    add_test (${MAIN}${idx} ${MAIN} ${arg})
    set_tests_properties (${MAIN}${idx} 
        PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro()

macro (TesterNoArg result)
    add_test (${MAIN}NoArg ${MAIN} ${arg})
    set_tests_properties (${MAIN}NoArg
        PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro()

# simply check segmentation fault or startup at all
macro (TesterRuns)
    add_test (${MAIN}Runs ${MAIN})
endmacro()

TesterRuns()
TesterNoArg("dudulu 1\nhardware=8")

set(testn 3)
# LESS must be all CAPS!!!
while (testn GREATER 2 AND testn LESS 50)
    MATH(EXPR testn "${testn} * 2") 
    Tester(${testn} "argc ${testn}${testn}")
endwhile()
