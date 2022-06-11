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
        Source/GameEngine/CollisionManager.cpp
        Source/GameEngine/Map.cpp
        Source/GamePlay/Bomberman.cpp
        Source/Logger/Logger.cpp
        Source/Raylib/Drawable/Cube.cpp
        Source/Raylib/Drawable/Drawable2D.cpp
        Source/Raylib/Drawable/Drawable3D.cpp
        Source/Raylib/Camera.cpp
        Source/Raylib/InputManager.cpp
        Source/Raylib/SoundManager.cpp
        Source/Raylib/Window.cpp)

#add Header files
FILE(GLOB HEADERFILES
        Source/ECS/ComponentPool.hpp
        Source/ECS/ECS.hpp
        Source/ECS/EntityManager.hpp
        Source/ECS/EntityViewer.hpp
        Source/GameEngine/CollisionManager.hpp
        Source/GameEngine/Map.hpp
        Source/GamePlay/Bomberman.hpp
        Source/GamePlay/CollisionSystem.hpp
        Source/GamePlay/Components.hpp
        Source/GamePlay/DrawSystem.hpp
        Source/GamePlay/ISystem.hpp
        Source/GamePlay/MovementSystem.hpp
        Source/Logger/Logger.hpp
        Source/Raylib/Drawables/Cube.hpp
        Source/Raylib/Drawables/Drawable2D.hpp
        Source/Raylib/Drawables/Drawable3D.hpp
        Source/Raylib/Drawables/IDrawable.hpp
        Source/Raylib/Camera.hpp
        Source/Raylib/InputManager.hpp
        Source/Raylib/RaylibTypeEncaps.hpp
        Source/Raylib/SoundManager.hpp
        Source/Raylib/Window.hpp)


#add to project
add_executable(bomberman ${HEADERFILES} ${CFILES} Source/GamePlay/Bomb.cpp Source/GamePlay/Timer.hpp Source/GamePlay/Explosion.cpp)

#add raylib

# add_executable(bomberman
#     Source/main.cpp
#     Source/Logger/Logger.cpp
# )

TARGET_LINK_LIBRARIES(bomberman raylib)

target_include_directories(bomberman PUBLIC Source Source/Logger)

add_subdirectory(Source/Raylib)
# add_subdirectory(Source/GameEngine)

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