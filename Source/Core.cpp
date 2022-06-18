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
    _soundManager = std::make_shared<RL::SoundManager>();

    RL::Vector3f cameraPos(0, 15, 8);
    _window->_camera.setPosition(cameraPos);
    _window->_camera.setRotation({0.0f, 1.0f, 0.0f });

    _startMenu = new Win::StartMenu(_window, _inputManager, _soundManager);
    _endMenu = new Win::EndMenu(_window, _inputManager, _soundManager);
    _pauseMenu = new Win::PauseMenu(_window, _inputManager, _soundManager);
    _settings = new Win::Settings(_window, _inputManager, _soundManager);
    _charSelec = new Win::CharacterSelect(_window, _inputManager, _soundManager);
    _mapSelect = new Win::MapSelect(_window, _inputManager, _soundManager);
    _prevS = 0;
    _prevM = 0;
    _screen = 0;

    _game = new Bomberman(_window, _inputManager, _map, _soundManager);
}

Core::~Core()
{
    _window->close();
    if (_game)
        delete _game;
    if (_startMenu)
        delete _startMenu;
    if (_endMenu)
        delete _endMenu;
    if (_settings)
        delete _settings;
    if (_pauseMenu)
        delete _pauseMenu;
    if (_charSelec)
        delete _charSelec;
    if (_mapSelect)
        delete _mapSelect;
}

void Core::startLoop()
{
   while (_window->isWindowOpen()) {
        switch (_screen) {
            case START_SCREEN:
                _screen = _startMenu->openStartMenu();
                _prevS = START_SCREEN;
                break;
            case CHAR_SCREEN:
                _screen = _charSelec->openCharSelect(_screen);
                _prevM = CHAR_SCREEN;
                break;
            case SETTINGS_SCREEN:
                _screen = _settings->openSettings(_prevS);
                break;
            case CLOSE:
                _window->close();
                break;
            case MAP_SCREEN:
                _screen = _mapSelect->openMapMenu(_prevM);
                _prevS = MAP_SCREEN;
                break;
            case GAME_SCREEN:
                _screen = GAME_SCREEN;
                if (!(_screen = _game->runFrame()))
                    _screen = CLOSE;
                break;
            case PAUSE_SCREEN:
                _screen = _pauseMenu->openPauseMenu();
                if (_screen == GAME_SCREEN)
                    this->_game->startGameTimers();
                if (_screen == START_SCREEN)
                    this->restartGame();
                _prevS = PAUSE_SCREEN;
                break;
            default:
                _screen = START_SCREEN;
                break;
        }
    }
}

void Core::restartGame()
{
    if (_game)
        delete _game;
    _window->clearDrawables();
    _game = new Bomberman(_window, _inputManager, _map, _soundManager);
}
