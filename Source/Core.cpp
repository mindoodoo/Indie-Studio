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
    }
    if (_screen == 6 || _screen == 4) {
        std::cout << "Will save the game:" << _screen << std::endl;
        _saveManager->saveMap(_map->getParsedMap());
        //save Items
        for (EntityID ent: EntityViewer<CollisionObjectType, Skillset, Pos, Sprite>(*_game->getEm().get())) {
            if (*_game->getEm()->Get<CollisionObjectType>(ent) == ITEM)
           if (!_game->getEm()->Get<Sprite>(ent)->model->checkIfHidden())
                   _saveManager->saveItem(ent, *_game->getEm()->Get<Pos>(ent), *_game->getEm()->Get<Skillset>(ent));
            }

        //save bomb
        for (EntityID ent: EntityViewer<CollisionObjectType, Skillset, BombOwner, Pos>(*_game->getEm().get())) {
            if (*_game->getEm()->Get<CollisionObjectType>(ent) == BOMB) {
                _saveManager->saveBomb(ent, *_game->getEm()->Get<Pos>(ent), *_game->getEm()->Get<Skillset>(ent),
                                       *_game->getEm()->Get<BombOwner>(ent));
            }
        }
        //save explosion
        for (EntityID ent: EntityViewer<CollisionObjectType, BombOwner, Pos>(*_game->getEm().get())) {
            if (*_game->getEm()->Get<CollisionObjectType>(ent) == EXPLOSION) {
                _saveManager->saveExplosion(ent, *_game->getEm()->Get<Pos>(ent), *_game->getEm()->Get<BombOwner>(ent));
            }
        }

        //save Player
        for (EntityID ent: EntityViewer<CollisionObjectType, BombCapacity, Skillset, Pos, Score>(*_game->getEm().get())) {
            if (*_game->getEm()->Get<CollisionObjectType>(ent) == PLAYER) {
                _saveManager->savePlayer(ent, *_game->getEm()->Get<Pos>(ent), *_game->getEm()->Get<Skillset>(ent), *_game->getEm()->Get<BombCapacity>(ent), *_game->getEm()->Get<Score>(ent));
            }
        }

        for (EntityID ent: EntityViewer<CollisionObjectType, BombCapacity, Skillset, Pos, Score>(*_game->getEm().get())) {
            if (*_game->getEm()->Get<CollisionObjectType>(ent) == AI) {
                _saveManager->saveAis(ent, *_game->getEm()->Get<Pos>(ent), *_game->getEm()->Get<Skillset>(ent), *_game->getEm()->Get<BombCapacity>(ent), *_game->getEm()->Get<Score>(ent));
            }
        }
        _saveManager->writeEntitys();
        std::cout << "Finished saving" << _screen << std::endl;
    }
}


void Core::startGame()
{
    _map = std::make_shared<RL::Map>(_saveManager->getMappath(), "./RaylibTesting/Assets/Maps/TestMap/TEST_WALL.png", "./RaylibTesting/Assets/Maps/TestMap/Floor.png", "./RaylibTesting/Assets/Maps/TestMap/crate.png", _saveManager->getLoading());
    //_saveManager->saveMap(_map->getParsedMap()); testing
    _game = new Bomberman(_window, _inputManager, _map, _soundManager);
}