CMAKE_MINIMUM_REQUIRED(VERSION 3.16)
project(bomberman)
set(CMAKE_CXX_STANDARD 20)

target_include_directories(bomberman PUBLIC . Drawables)

target_sources(bomberman PUBLIC
    Camera.cpp
    InputManager.cpp
    Drawables/Cube.cpp
    SoundManager.cpp
    Window.cpp
    Drawables/Drawable2D.cpp
    Drawables/Drawable3D.cpp
)
