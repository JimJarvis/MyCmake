add_definitions(-std=c++11 -pthread)

set(CONFIGURED_ONCE TRUE CACHE INTERNAL
    "A flag showing that CMake has configured at least once.")

function (link_thread target)
    # same effect:
    # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")
    target_link_libraries(${target} -pthread)
endfunction()

function (add_thread target)
    add_executable(${target} ${ARGN})
    target_link_libraries(${target} -pthread)
endfunction()
