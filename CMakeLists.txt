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
        Source/main.cpp
        Source/Drawable2D.cpp
        Source/Drawable3D.cpp
        Source/Window.cpp
        Source/Logger.cpp
        Source/Map.cpp
        Source/Renderer.cpp
        Source/InputManager.cpp
        Source/GamePlay/Bomberman.cpp)

#add Header files
FILE(GLOB HEADERFILES
        Source/ECS/ComponentPool.hpp
        Source/ECS/ECS.hpp
        Source/ECS/EntityManager.hpp
        Source/ECS/EntityViewer.hpp
        Source/GamePlay/Bomberman.hpp
        Source/GamePlay/CollisionSystem.hpp
        Source/GamePlay/Components.hpp
        Source/GamePlay/DrawSystem.hpp
        Source/GamePlay/ISystem.hpp
        Source/GamePlay/MovementSystem.hpp
        Source/InputManager.hpp
        Source/Renderer.hpp
        Source/Map.hpp
        Source/Drawable2D.hpp
        Source/Drawable3D.hpp
        Source/IDrawable.hpp
        Source/Window.hpp
        Source/Logger.hpp
        Source/RaylibTypeEncaps.hpp)


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