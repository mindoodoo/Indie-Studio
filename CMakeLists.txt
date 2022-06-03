CMAKE_MINIMUM_REQUIRED(VERSION 3.16)
project(bomberman)
set(CMAKE_CXX_STANDARD 20)

include_directories(Source)
add_executable(bomberman Source/main.cpp 
    Source/ECS/ComponentPool.hpp Source/ECS/ECS.hpp Source/ECS/EntityManager.hpp Source/ECS/EntityViewer.hpp
    Source/GamePlay/Bomberman.cpp Source/GamePlay/Bomberman.hpp Source/GamePlay/CollisionSystem.hpp Source/GamePlay/Components.hpp Source/GamePlay/DrawSystem.hpp Source/GamePlay/ISystem.hpp Source/GamePlay/MovementSystem.hpp
    Source/InputManager.cpp
    Source/InputManager.hpp
    Source/Renderer.cpp
    Source/Renderer.hpp
    Source/Map.cpp
    Source/Map.hpp
    Source/IDrawable.hpp
    Source/Drawable2D.cpp
    Source/Drawable2D.hpp
    Source/Drawable3D.cpp
    Source/Drawable3D.hpp
    Source/Window.cpp
    Source/Window.hpp
    Source/Logger.cpp
    Source/Logger.hpp
    Source/RaylibTypeEncaps.hpp)
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
endif()

TARGET_LINK_LIBRARIES(bomberman raylib)
