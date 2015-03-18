message("Folder src/")

set(MAIN
    main)

set(SOURCES 
    ${MAIN}.cpp)

add_thread(${MAIN} ${SOURCES})

# ==== boost ====
include(eona_boost)

link_boost(${MAIN} ${Boost_LIBRARIES})

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

# ==== CTest (cmake default) ====
include(eona_ctest)
