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
     _saveManager = std::make_shared<RL::SaveManager>();
     _soundManager = std::make_shared<RL::SoundManager>();


    RL::Vector3f cameraPos(0, 15, 8);
    _window->_camera.setPosition(cameraPos);
    _window->_camera.setRotation({0.0f, 1.0f, 0.0f });
    _game = NULL;
    _startMenu = new Win::StartMenu(_window, _inputManager, _soundManager, _saveManager);
    _endMenu = new Win::EndMenu(_window, _inputManager, _soundManager, _saveManager);
    _pauseMenu = new Win::PauseMenu(_window, _inputManager, _soundManager, _saveManager);
    _settings = new Win::Settings(_window, _inputManager, _soundManager, _saveManager);
    _charSelec = new Win::CharacterSelect(_window, _inputManager, _soundManager, _saveManager);
    _mapSelect = new Win::MapSelect(_window, _inputManager, _soundManager, _saveManager);
    _prevS = 0;
    _prevM = 0;
    _screen = 0;
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
            case 0:
                _screen = _startMenu->openStartMenu();
                _prevS = 0;
                break;
            case 1:
                _screen = _charSelec->openCharSelect(_screen);
                _prevM = 1;
                break;
            case 2:
                _screen = _charSelec->openCharSelect(_screen);
                _prevM = 2;
                break;
            case 3:
                _screen = _settings->openSettings(_prevS);
                break;
            case 4:
                _window->close();
                break;
            case 5:
                _screen = _mapSelect->openMapMenu(_prevM);
                _prevS = 5;
                break;
            case 6:
                if (!_game)
                    startGame();
                if (!_game->runFrame())
                    _screen = 4;
                break;
            case 7:
                _screen = _pauseMenu->openPauseMenu();
                _prevS = 7;
                break;
            case 8:
                //TODO INSERT LOAD here!
                _saveManager->updateMap(-1);
                _screen = 6;
                break;
            default:
                _screen = 0;
                break;
        }
        // if (!_game->runFrame())
        //     break;
    }
}

void sortPlayerChoices(Win::CharacterSelect *_charSelec)
{
    PlayerChoice temp;
    if (_charSelec->_playerChoice.size() > 1) {
        if (_charSelec->_playerChoice[0].playerOrder > _charSelec->_playerChoice[1].playerOrder) {
            temp = _charSelec->_playerChoice[0];
            _charSelec->_playerChoice[0] = _charSelec->_playerChoice[1];
            _charSelec->_playerChoice[1] = temp;
        }
    }
    int checked = 0;
    for(int i = 0; i < 4; i++) {
        for (int j = 0; j <_charSelec->_playerChoice.size(); j++) {
            if (_charSelec->_playerChoice[j].Character == i)
                checked = 1;                               
        }
        if (checked == 0) 
            _charSelec->_playerChoice.push_back(_charSelec->fillOutPlayerChoice(i, true, _charSelec->_playerChoice.size() + 1));
        checked = 0;
    }
}

void Core::startGame()
{
    sortPlayerChoices(_charSelec);
    _map = std::make_shared<RL::Map>(_saveManager->getMappath(), "./RaylibTesting/Assets/Maps/TestMap/TEST_WALL.png", "./RaylibTesting/Assets/Maps/TestMap/Floor.png", "./RaylibTesting/Assets/Maps/TestMap/crate.png");
    //_saveManager->saveMap(_map->getParsedMap()); testing
    _game = new Bomberman(_window, _inputManager, _map, _soundManager, _charSelec->_playerChoice);
}