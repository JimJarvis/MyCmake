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

target_link_libraries(${MAIN} -pthread)
# same effect:
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")

# ==== boost ====
if (NOT DEFINED     BOOST_ROOT        AND
    NOT DEFINED ENV{BOOST_ROOT}       AND
    NOT DEFINED     BOOST_INCLUDEDIR  AND
    NOT DEFINED ENV{BOOST_INCLUDEDIR} AND
    NOT DEFINED     BOOST_LIBRARYDIR  AND
    NOT DEFINED ENV{BOOST_LIBRARYDIR})
    if (APPLE OR UNIX)
        # default: /include and /lib
        set(BOOST_ROOT "/opt/boost/")
    elseif (WIN32)
        set(BOOST_INCLUDEDIR "C:/local/boost_1_55_0")
        set(BOOST_LIBRARYDIR "C:/local/boost_1_55_0/lib32-msvc-10.0")
    elseif (UNIX)
       #set if not default by BOOST_ROOT:
       #set(BOOST_INCLUDEDIR "/opt/boost/include")
       #set(BOOST_LIBRARYDIR "/opt/boost/lib")
    endif()
endif()
# otherwise Mac dynamical lib doesn't work
if (APPLE OR WIN32)
    set(Boost_USE_STATIC_LIBS TRUE)
endif()

find_package(Boost COMPONENTS 
    program_options
    thread
    system
    chrono
    date_time
    REQUIRED)

# SYSTEM arg tells compiler that the path contains system files. Compiler will thus ignore warning. 
include_directories(SYSTEM ${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})
target_link_libraries(${MAIN} ${Boost_LIBRARIES})

set(CONFIGURED_ONCE TRUE CACHE INTERNAL
    "A flag showing that CMake has configured at least once.")

# for boost testing ONLY

add_executable(boosttest boosttest.cpp)
target_link_libraries(boosttest ${Boost_LIBRARIES})

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
enable_testing()

if (NOT DEFINED GTEST_ROOT)
    if (APPLE OR UNIX)
        set(GTEST_ROOT "/opt/gtest")
    endif()
endif()

# Workaround OS-specific problems
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # force this option to ON so that Google Test will use /MD instead of /MT
    # /MD is now the default for Visual Studio, so it should be our default, too
    option(gtest_force_shared_crt
        "Use shared (DLL) run-time lib even when Google Test is built as static lib."
        ON)
elseif (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE=1)
endif()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# add_gtest(<target> <sources>...)
#
#  Adds a GTest test executable, <target>, built from <sources> and
#  adds the test so that CTest will run it. Both the executable and the test
#  will be named <target>.
#
# additional args can be accessed via ARG0, ARG1 ... ARGN
function(add_gtest target)
    add_executable(${target} ${ARGN})
    target_link_libraries(mygtest ${GTEST_BOTH_LIBRARIES})
    target_link_libraries(mygtest ${Boost_LIBRARYDIR})
    target_link_libraries(mygtest -pthread)
    target_link_libraries(${target} gmock_main)
    add_test(${target} ${target})
endfunction()

add_gtest(mygtest mygtest.cpp)


# ==== CTest (cmake default) ====
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
