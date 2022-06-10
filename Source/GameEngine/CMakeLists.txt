CMAKE_MINIMUM_REQUIRED(VERSION 3.16)
project(bomberman)
set(CMAKE_CXX_STANDARD 20)

target_include_directories(bomberman PUBLIC .)

target_sources(bomberman PUBLIC
    CollisionManager.cpp
    Map.cpp
)
