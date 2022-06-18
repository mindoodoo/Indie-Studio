/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** Bomberman
*/

#include "Bomberman.hpp"

Bomberman::Bomberman(std::shared_ptr<RL::Window> Window, std::shared_ptr<RL::InputManager> InputManager, std::shared_ptr<RL::Map> Map, std::shared_ptr<RL::SoundManager> SoundManager)
    : _window(Window), _map(Map), _inputManager(InputManager), _soundManager(SoundManager)
{
    _em = std::make_shared<EntityManager>();

    // Take care with system order when adding to vector
    _systems.push_back(std::make_shared<CollisionSystem>(_em, _window, _soundManager, _map));
    _systems.push_back(std::make_shared<MovementSystem>(_em, _map, _inputManager));
    _systems.push_back(std::make_shared<AISystem>(_em, _map));
    _systems.push_back(std::make_shared<DrawSystem>(_em, _map));
    
    _allModels.push_back(RL::Drawable3D("./RaylibTesting/Assets/3d_models/Skull/Skull.png", "./RaylibTesting/Assets/Bomb/Bomb.obj", "", RL::MODEL, 2));
    _allModels.push_back(RL::Drawable3D("./RaylibTesting/Assets/Explosion/textures/fire.png", "./RaylibTesting/Assets/Explosion/textures/fire.iqm", "./RaylibTesting/Assets/Explosion/textures/fire.iqm", RL::MODEL, 3));
    
    createPlayer({13, 11, 1});
    createPlayer({1, 1, 1});
    createAI({13, 1, 1});
    createAI({1, 11, 1});
    generateItems();

    _gameTimer.startTimer();
    _deltaTimer.startTimer();
    _gamePaused = false;
    this->_pauseGame = false;
}

Bomberman::~Bomberman()
{
}

void Bomberman::generateItems()
{
    int wallPassAmount = 1;
    int placeItem;

    for (int i = 0; i < _map->getMapDepth(); i++) {
        for (int j = 0; j < _map->getMapWidth(); j++) {
            if (_map->getParsedMap()[i][j].tile == 2) {
                placeItem = rand() % 100;
                if (placeItem > 77) {
                    switch (rand() % 4) {
                        case 0:
                            createSpeedUpItem({(float)j, (float)i, 1});
                            break;
                        case 1:
                            createBombUpItem({(float)j, (float)i, 1});
                            break;
                        case 2:
                            createFireUpItem({(float)j, (float)i, 1});
                            break;
                        case 3:
                            if (wallPassAmount) {
                                wallPassAmount--;
                                createWallPassItem({(float)j, (float)i, 1});
                            }
                            break;
                    }
                }
            }
        }
    }
}

float translateFigureCoordinates(float pos, int borderSize)
{
    float newpos = pos - (borderSize / 2);
    if (borderSize % 2 == 0)
        newpos += 0.5;
    return newpos;
}

void Bomberman::createPlayer(Pos pos)
{
    EntityID id = _em->CreateNewEntity();
    std::string playtex = "./RaylibTesting/Assets/3d_models/Players/PlayerFour.png";
    std::string playermod = "./RaylibTesting/Assets/3d_models/Players/playerFour.iqm";
    std::string playeranim = playermod;

    _player.push_back(id);
    _em->Assign<Pos>(id, pos);
    _em->Assign<Velocity>(id, {0.08,0.08});
    _em->Assign<Input>(id, Input{NONE});
    _em->Assign<Score>(id, Score{0});
    _em->Assign<Health>(id, Health{100});
    _em->Assign<Skillset>(id, Skillset{0, 0, 1, false});
    _em->Assign<BombCapacity>(id, BombCapacity{3, 3});
    _em->Assign<CollisionObjectType>(id, CollisionObjectType{PLAYER});

    RL::Drawable3D *Player = new RL::Drawable3D(playtex, playermod, playeranim, RL::MODEL, 0.25);
    Player->setPosition((RL::Vector3f){
        translateFigureCoordinates(pos.x, _map->getMapWidth()),
        pos.y,
        translateFigureCoordinates(pos.y, _map->getMapDepth())
    });
    _em->Assign<Sprite>(id, Sprite{Player});
    _window->queueDrawable(Player);
}

void Bomberman::createAI(Pos pos)
{
    EntityID id = _em->CreateNewEntity();
    std::string aitex = "./RaylibTesting/Assets/3d_models/Players/PlayerFour.png";
    std::string aimod = "./RaylibTesting/Assets/3d_models/Players/playerFour.iqm";

    _player.push_back(id);
    _em->Assign<Pos>(id, pos);
    _em->Assign<Velocity>(id, {0.04,0.04});
    _em->Assign<Input>(id, Input{NONE});
    _em->Assign<Score>(id, Score{0});
    _em->Assign<Health>(id, Health{100});
    _em->Assign<Skillset>(id, Skillset{0, 0, 1, false});
    _em->Assign<BombCapacity>(id, BombCapacity{3, 3});
    _em->Assign<CollisionObjectType>(id, CollisionObjectType{AI});

    AIData data = {false, {0, 0, 0}, RANDOM, 5, {}, {1, 2}};
    _em->Assign<AIData>(id, data);

    RL::Drawable3D *AI = new RL::Drawable3D(aitex, aimod, aimod, RL::MODEL, 0.25);
    AI->setPosition((RL::Vector3f){
        translateFigureCoordinates(pos.x, _map->getMapWidth()),
        pos.y,
        translateFigureCoordinates(pos.y, _map->getMapDepth())
    });
    _em->Assign<Sprite>(id, Sprite{AI});
    _window->queueDrawable(AI);
}

void Bomberman::createSpeedUpItem(Pos pos)
{
    EntityID id = _em->CreateNewEntity();
    _em->Assign<Pos>(id, pos);
    _em->Assign<Skillset>(id, Skillset{0, 1, 0, false});
    _em->Assign<CollisionObjectType>(id, CollisionObjectType{ITEM});
    _em->Assign<ItemType>(id, ItemType{SPEED_UP});
    std::string speedUpPath = "./Source/PowerUps/Speed.png";
    RL::Drawable3D *speedUp = new RL::Drawable3D(speedUpPath, "", "", RL::POWER);
    speedUp->setPosition((RL::Vector3f){
        translateFigureCoordinates(pos.x, _map->getMapWidth()),
        1.0f,
        translateFigureCoordinates(pos.y, _map->getMapDepth())
    });
    speedUp->setHidden(true);
    _em->Assign<Sprite>(id, Sprite{speedUp});
    _window->queueDrawable(speedUp);
}

void Bomberman::createBombUpItem(Pos pos)
{
    EntityID id = _em->CreateNewEntity();
    _em->Assign<Pos>(id, pos);
    _em->Assign<Skillset>(id, Skillset{1, 0, 0, false});
    _em->Assign<CollisionObjectType>(id, CollisionObjectType{ITEM});
    _em->Assign<ItemType>(id, ItemType{BOMB_UP});
    std::string bombUpPath = "./Source/PowerUps/BombUp.png";
    RL::Drawable3D *bombUp = new RL::Drawable3D(bombUpPath, "", "", RL::POWER);
    bombUp->setPosition((RL::Vector3f){
        translateFigureCoordinates(pos.x, _map->getMapWidth()),
        1.0f,
        translateFigureCoordinates(pos.y, _map->getMapDepth())
    });
    bombUp->setHidden(true);
    _em->Assign<Sprite>(id, Sprite{bombUp});
    _window->queueDrawable(bombUp);
}

void Bomberman::createFireUpItem(Pos pos)
{
    EntityID id = _em->CreateNewEntity();
    _em->Assign<Pos>(id, pos);
    _em->Assign<Skillset>(id, Skillset{0, 0, 1, false});
    _em->Assign<CollisionObjectType>(id, CollisionObjectType{ITEM});
    _em->Assign<ItemType>(id, ItemType{FIRE_UP});
    std::string fireUpPath = "./Source/PowerUps/PowerUp.png";
    RL::Drawable3D *fireUp = new RL::Drawable3D(fireUpPath, "", "", RL::POWER);
    fireUp->setPosition((RL::Vector3f){
        translateFigureCoordinates(pos.x, _map->getMapWidth()),
        1.0f,
        translateFigureCoordinates(pos.y, _map->getMapDepth())
    });
    fireUp->setHidden(true);
    _em->Assign<Sprite>(id, Sprite{fireUp});
    _window->queueDrawable(fireUp);
}

void Bomberman::createWallPassItem(Pos pos)
{
    EntityID id = _em->CreateNewEntity();
    _em->Assign<Pos>(id, pos);
    _em->Assign<Skillset>(id, Skillset{0, 0, 0, true});
    _em->Assign<CollisionObjectType>(id, CollisionObjectType{ITEM});
    _em->Assign<ItemType>(id, ItemType{WALLPASS});
    std::string wallPassPath = "./Source/PowerUps/WallsWalkable.png";
    RL::Drawable3D *wallPass = new RL::Drawable3D(wallPassPath, "", "", RL::POWER);
    wallPass->setPosition((RL::Vector3f){
        translateFigureCoordinates(pos.x, _map->getMapWidth()),
        1.0f,
        translateFigureCoordinates(pos.y, _map->getMapDepth())
    });
    wallPass->setHidden(true);
    _em->Assign<Sprite>(id, Sprite{wallPass});
    _window->queueDrawable(wallPass);
}

void Bomberman::createMonster(Pos pos)
{
    EntityID id = _em->CreateNewEntity();
    _em->Assign<Pos>(id, pos);
    _em->Assign<Velocity>(id, {0.1,0.1});
    _em->Assign<Score>(id, Score{0}); //defines how player score increases when killing monster
    _em->Assign<Health>(id, Health{100});
    _em->Assign<CollisionObjectType>(id, CollisionObjectType{MONSTER});

    std::string skulltex = "./RaylibTesting/Assets/3d_models/Skull/Skull.png";
    std::string skullmod = "./RaylibTesting/Assets/3d_models/Skull/Skull.obj";
    RL::Drawable3D *Skull = new RL::Drawable3D(skulltex, skullmod, "", RL::MODEL, 0.04);
    Skull->setPosition((RL::Vector3f){
        translateFigureCoordinates(pos.x, _map->getMapWidth()),
        pos.y,
        translateFigureCoordinates(pos.y, _map->getMapDepth())
    });
    _em->Assign<Sprite>(id, Sprite{Skull});
    _window->queueDrawable(Skull);
}

void savePlayerInput(Input* playerInput, UserInput input, bool &newInput)
{
    playerInput->pressedKey = (UserInput)input;
    newInput = true;
}

void Bomberman::getFirstPlayerInput()
{
    if (_player[One] == INVALID_ENTITY)
        return;
    Input* playerInput = _em->Get<Input>(_player[One]);

    if (!_event.size())
        playerInput->pressedKey = NONE;

    bool newInput = false;

    if (_inputManager->playerHasPressedKeyAsChar(UP))
        savePlayerInput(playerInput, UP, newInput);
    if (_inputManager->playerHasPressedKeyAsChar(DOWN))
        savePlayerInput(playerInput, DOWN, newInput);
    if (_inputManager->playerHasPressedKeyAsChar(LEFT))
        savePlayerInput(playerInput, LEFT, newInput);
    if (_inputManager->playerHasPressedKeyAsChar(RIGHT))
        savePlayerInput(playerInput, RIGHT, newInput);
    if (_inputManager->playerHasPressedKeyAsChar(LAY_BOMB)) {
        savePlayerInput(playerInput, LAY_BOMB, newInput);
        layBomb(_player[One]);
    }
    if (!newInput)
        playerInput->pressedKey = NONE;
}

void Bomberman::getSecondPlayerInput()
{
    if (_player[Two] == INVALID_ENTITY)
        return;
    Input* playerInput = _em->Get<Input>(_player[Two]);

    if (!_event.size())
        playerInput->pressedKey = NONE;

    bool newInput = false;

    if (_inputManager->playerHasPressedKeyAsChar(UP2))
        savePlayerInput(playerInput, UP2, newInput);
    if (_inputManager->playerHasPressedKeyAsChar(DOWN2))
        savePlayerInput(playerInput, DOWN2, newInput);
    if (_inputManager->playerHasPressedKeyAsChar(LEFT2))
        savePlayerInput(playerInput, LEFT2, newInput);
    if (_inputManager->playerHasPressedKeyAsChar(RIGHT2))
        savePlayerInput(playerInput, RIGHT2, newInput);
    if (_inputManager->playerHasPressedKeyAsChar(LAY_BOMB2)) {
        savePlayerInput(playerInput, LAY_BOMB2, newInput);
        layBomb(_player[Two]);
    }
    if (!newInput)
        playerInput->pressedKey = NONE;
}

void Bomberman::checkInput()
{
    if (this->_inputManager->playerHasPressedKeyAsChar(ESCAPE) && !this->_gamePaused) {
        this->stopGameTimers();
        return;
    }
    getFirstPlayerInput();
    getSecondPlayerInput();
}

void Bomberman::startGameTimers()
{
    if (!_gamePaused) {
        _gameTimer.restartTimer();
    } else {
        _gameTimer.stopPause();
        _gamePaused = false;
    }
    _deltaTimer.restartTimer();
    this->resumeBombCounters();
}

void Bomberman::stopGameTimers()
{
    _gamePaused = true;
    _gameTimer.startPause();
    this->pauseBombCounters();
}

bool Bomberman::checkIfVectorContain(std::vector<EntityID> vector, EntityID id) {
    if (std::find(vector.begin(), vector.end(), id) != vector.end())
        return true;
    return false;
}

// event as argument?
int Bomberman::runFrame()
{
    _soundManager->updateMusicStream();
    _inputManager->popInputs();
    _inputManager->recordInputs();
    _event = _inputManager->getInputs();
    _aiBombLaying.clear();
  
    checkInput();
    if (this->_gamePaused && !this->_pauseGame) {
        this->_pauseGame = true;
        return 7;
    }
    if (!this->_gamePaused && this->_pauseGame)
        this->_pauseGame = false;
    checkBombalive();
    checkExplosionalive();
    for (std::shared_ptr<ISystem> system : _systems)
        system->update(_deltaTimer.returnTime(), _player, _aiBombLaying);
    for (EntityID id : _aiBombLaying) {
        if (checkIfVectorContain(_player, id))
            layBomb(id);
    }
    if (isGameEnd())
        return 8;
    startDrawScene();
    _deltaTimer.restartTimer();
    return 6;
}

void Bomberman::startDrawScene()
{
    _window->displayDrawables(*_map.get());
    _window->clearWindow(BLACK);
}

void Bomberman::stopDrawScene()
{
}

bool Bomberman::isGameEnd()
{
    int count = 0;
    
    for (EntityID id : _player)
        if (id != INVALID_ENTITY)
            count++;

    if (count <= 1)
        return true;

    return false;
}
