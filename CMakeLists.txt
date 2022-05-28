CMAKE_MINIMUM_REQUIRED(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)

#check if windows and set compilepath
if (WIN32)
    message("set path for windows")
    set( CMAKE_CXX_COMPILER "/pathto/g++" )
    set( CMAKE_C_COMPILER "/pathto/gcc" )
endif(WIN32)

project(bomberman VERSION 0.0)

#add C files
FILE(GLOB CFILES
        Source/main.cpp)

#add Header files
FILE(GLOB HEADERFILES
        Source/sample.h)


#add to project
add_executable(bomberman ${HEADERFILES} ${CFILES})

#add raylib
if (NOT raylib_FOUND)
    INCLUDE(FetchContent)
    FetchContent_Declare(raylib URL https://github.com/raysan5/raylib/archive/refs/tags/4.0.0.tar.gz)
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED)
        SET(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        SET(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        ADD_SUBDIRECTORY(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
        SET(raylib_FOUND TRUE)
    endif()
    TARGET_LINK_LIBRARIES(bomberman raylib)
endif()