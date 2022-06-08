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
        Source/testGamePlay.cpp
        Source/CollisionManager.cpp
        Source/Drawable2D.cpp
        Source/Drawable3D.cpp
        Source/InputManager.cpp
        Source/Logger.cpp
        Source/Map.cpp
        Source/Renderer.cpp
        Source/SoundManager.cpp
        Source/Window.cpp
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
        Source/CollisionManager.hpp
        Source/Drawable2D.hpp
        Source/Drawable3D.hpp
        Source/IDrawable.hpp
        Source/InputManager.hpp
        Source/Logger.hpp
        Source/Map.hpp
        Source/RaylibTypeEncaps.hpp
        Source/Renderer.hpp
        Source/SoundManager.hpp
        Source/Window.hpp)


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