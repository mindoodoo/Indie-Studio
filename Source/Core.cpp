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
    _saveManager = std::make_shared<RL::SaveManager>();
    _inputManager = std::make_shared<RL::InputManager>();
    _soundManager = std::make_shared<RL::SoundManager>();


    RL::Vector3f cameraPos(0, 19, 7.5);
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

void Core::saveGame() {
    std::cout << "Will save the game:" << _screen << std::endl;
    _saveManager->clearBeforeSafe();
    _saveManager->saveMap(_map->getParsedMap());
    //save Items
    for (EntityID ent: EntityViewer<CollisionObjectType, Skillset, Pos, Sprite>(*_game->getEm().get())) {
        if (*_game->getEm()->Get<CollisionObjectType>(ent) == ITEM)
            if (!_game->getEm()->Get<Sprite>(ent)->model->checkIfHidden())
                _saveManager->saveItem(ent, *_game->getEm()->Get<Pos>(ent), *_game->getEm()->Get<Skillset>(ent));
    }

    //save bomb
    for (EntityID ent: EntityViewer<CollisionObjectType, Skillset, BombOwner, Pos, Timer>(*_game->getEm().get())) {
        if (*_game->getEm()->Get<CollisionObjectType>(ent) == BOMB) {
            _saveManager->saveBomb(ent, *_game->getEm()->Get<Pos>(ent), *_game->getEm()->Get<Skillset>(ent),
                                   *_game->getEm()->Get<BombOwner>(ent), _game->getEm()->Get<Timer>(ent)->returnBombTime());
        }
    }
    //save explosion
    for (EntityID ent: EntityViewer<CollisionObjectType, BombOwner, Pos, Timer>(*_game->getEm().get())) {
        if (*_game->getEm()->Get<CollisionObjectType>(ent) == EXPLOSION) {
            _saveManager->saveExplosion(ent, *_game->getEm()->Get<Pos>(ent), *_game->getEm()->Get<BombOwner>(ent), _game->getEm()->Get<Timer>(ent)->returnBombTime());
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
    _screen = PAUSE_SCREEN;
}


void Core::startLoop() {
    while (_window->isWindowOpen()) {
        // _soundManager->updateMusicStream();
        // _soundManager->playSpecificMusic("BackgroundMusicOne");
        switch (_screen) {
            case START_SCREEN:
                //_charSelec->clearCharSelected();
                _screen = _startMenu->openStartMenu();
                _prevS = START_SCREEN;
                break;
            case CHAR_SCREEN:
                _screen = _charSelec->openCharSelect(_screen);
                _prevM = CHAR_SCREEN;
                break;
            case CHAR_SELEC_TWO:
                _screen = _charSelec->openCharSelect(_screen);
                _prevM = CHAR_SELEC_TWO;
                break;
            case SETTINGS_SCREEN:
                _screen = _settings->openSettings(_prevS);
                break;
            case CLOSE:
                _window->close();
                break;
            case MAP_SCREEN:
                _screen = _mapSelect->openMapMenu(_prevM);
                std::cout << "TEEEEEEEST: " << _screen << std::endl;
                _prevS = MAP_SCREEN;
                break;
            case 6:
                if (!_game) {
                    std::cout << "HAVE TO START A NEW GAME" << std::endl;
                    this->startGame();
                    break;
                } else {
                    std::cout << "STILL HAVE A RUNNING GAME" << std::endl;
                }

                if (!(_screen = _game->runFrame())) {
                    //  std::cout <<"test2" << std::endl;
                    _screen = 4;
                }
                if (_screen == 8)
                    this->killGame();
                break;
            case PAUSE_SCREEN:
                _screen = _pauseMenu->openPauseMenu();
                if (_screen == GAME_SCREEN) {
                    this->startGame();
                    this->_game->startGameTimers();
                }
                if (_screen == START_SCREEN)
                    this->killGame();
                if (_screen == 99)
                    saveGame();
                _prevS = PAUSE_SCREEN;
                break;
            case END_SCREEN:
                _screen = this->_endMenu->openEndMenu();
                break;
            case INTRO:
                _screen = this->_startMenu->starIntro();
                break;
            case LOAD:
                _saveManager->updateMap(-1);
                _screen = 6;
                break;
            default:
                _screen = INTRO;
                break;
        }
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

void Core::killGame()
{
    std::cout << "KILL GAME" << std::endl;
    if (_game)
        delete _game;
    if (_map)
        _map.reset();
    _window->clearDrawables();
    _game = nullptr;
}

void Core::startGame()
{
    std::cout << "START" << std::endl;
    sortPlayerChoices(_charSelec);
    _map = std::make_shared<RL::Map>(_saveManager->getMappath(), _saveManager->getWallTexture(), _saveManager->getFloorTexture(), _saveManager->getCrateTexture(), _saveManager->getLoading());
    _game = new Bomberman(_window, _inputManager, _map, _soundManager, _saveManager, _charSelec->_playerChoice);
    std::cout << "Stsart DONE" << std::endl;
}
