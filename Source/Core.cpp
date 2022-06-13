/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** Core
*/

#include "Core.hpp"

Core::Core()
{
    _window = std::make_shared<RL::Window>("INDIE_STUDIO");
    _inputManager = std::make_shared<RL::InputManager>();
    _map = std::make_shared<RL::Map>("./RaylibTesting/Assets/Maps/TestMap/test.csv", "./RaylibTesting/Assets/Maps/TestMap/TEST_WALL.png", "./RaylibTesting/Assets/Maps/TestMap/Floor.png", "./RaylibTesting/Assets/Maps/TestMap/crate.png");

    SetTargetFPS(60);
    RL::Vector3f cameraPos(0, 15, 8);
    _window->_camera.setPosition(cameraPos);
    _window->_camera.setRotation({0.0f, 1.0f, 0.0f });

    _game = new Bomberman(_window, _inputManager, _map);
}

Core::~Core()
{
    _window->close();
    if (_game)
        delete _game;
}

void Core::startLoop()
{
    while (_window->isWindowOpen()) {
        if (!_game->runFrame())
            break;
    }
}
