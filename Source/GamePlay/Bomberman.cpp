/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** Bomberman
*/

#include "Bomberman.hpp"

Bomberman::Bomberman(std::shared_ptr<RL::Window> Window, std::shared_ptr<RL::InputManager> InputManager, std::shared_ptr<RL::Map> Map, std::shared_ptr<RL::SoundManager> SoundManager, std::vector<PlayerChoice> playerChoices)
    : _window(Window), _map(Map), _inputManager(InputManager), _soundManager(SoundManager), _background("./RaylibTesting/Assets/Background/background1.png")
{
    _background.resize(_window->getDimensions());
    _em = std::make_shared<EntityManager>();
    // take care with system order when adding to vector
    _systems.push_back(std::make_shared<CollisionSystem>(_em, _window, _soundManager, _map));
    _systems.push_back(std::make_shared<MovementSystem>(_em, _map, _inputManager));
    _systems.push_back(std::make_shared<AISystem>(_em, _map));
    _systems.push_back(std::make_shared<DrawSystem>(_em, _map));
    _allModels.push_back(RL::Drawable3D("./RaylibTesting/Assets/3d_models/Skull/Skull.png", "./RaylibTesting/Assets/Bomb/Bomb.obj", "", RL::MODEL, 2));
    _allModels.push_back(RL::Drawable3D("./RaylibTesting/Assets/Explosion/textures/fire.png", "./RaylibTesting/Assets/Explosion/textures/fire.iqm", "./RaylibTesting/Assets/Explosion/textures/fire.iqm", RL::MODEL, 3));

    _allIcons.push_back(new RL::Drawable2D("./RaylibTesting/Assets/2d_models/iconOne.png"));
    _allIcons.push_back(new RL::Drawable2D("./RaylibTesting/Assets/2d_models/iconTwo.png"));
    _allIcons.push_back(new RL::Drawable2D("./RaylibTesting/Assets/2d_models/iconThree.png"));
    _allIcons.push_back(new RL::Drawable2D("./RaylibTesting/Assets/2d_models/iconFour.png"));

    //assume we receve our vector of player orders typedef INFO { int (1 or 2 or 3 or 4), bool player}
    // for (i  in ....) {
    //_allIcons[vector[i].int].setPosition( SET THE PoSiTION)
    //_window queueDrawable(_allicons[vector[i].int])
    //
    //}

    for ( int i = 0; i < _allIcons.size(); i++ ){
        _allIcons[playerChoices[i].Character]->resize({60,60});
        _allIcons[playerChoices[i].Character]->setPosition((i * _window->getDimensions().x * 20 / 100) + (_window->getDimensions().x / 100 * 13), 0, 0);
        _window->queueDrawable(_allIcons[i]);
    }
    // _window->queueDrawable(_allIcons[0]);
    // _window->queueDrawable(_allIcons[1]);
    // _window->queueDrawable(_allIcons[2]);
    // _window->queueDrawable(_allIcons[3]);




    //erase the begigining
    //_allIcons.erase(_allIcons.begin());

    
    //this is respndible for the music being played then shuffle enabled, comment out to cancel
    //_soundManager->playRandomMusic();
    //_soundManager->enableDisableShuffle();
    
    // if only one player, fill _player[1] with INVALID_ENTITY
    // TODO: make pos dependant from map size
    std::vector<Pos>playerStartPositions;
    playerStartPositions.push_back({13, 11, 1});
    playerStartPositions.push_back({1, 1, 1});
    playerStartPositions.push_back({13, 1, 1});
    playerStartPositions.push_back({1, 11, 1});


    
    for (int i = 0 ; i < playerChoices.size(); i++) {
        std::cout << "choices: " << playerChoices[i].CPU << std::endl;
        if (playerChoices[i].CPU == false) 
            createPlayer(playerStartPositions[i], playerChoices[i].Character);
        else {
            if (i == 1)
                _player.push_back(INVALID_ENTITY);
            createAI(playerStartPositions[i], playerChoices[i].Character);

        }
    }


    // createPlayer({13, 11, 1});
    // createPlayer({1, 1, 1});
    // createAI({13, 1, 1});
    // createAI({1, 11, 1});
    generateItems();
    // createSpeedUpItem({10, 10, 1});
    // createSpeedUpItem({4, 3, 1});
    // createBombUpItem({8, 5, 1});
    // createBombUpItem({9, 5, 1});
    // createFireUpItem({10, 5, 1});
    // createWallPassItem({2, 3, 1});
    // createBomb({5, 5, 1}, _player.back());
    // createMonster({5, 5, 1});


    // HERE ADD CORRESPONDING 2DMODELS TO THE ENTITIES IN GAME
    // 1 2 3 4 == 1 2 3 4
    _gamePaused = false;
    _gameTimer.startTimer();
    _deltaTimer.startTimer();
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


//little function to fetch paths of characters
std::vector<std::string> findCharPaths(int character)
{
    std::vector<std::string> charPaths;
    if (character == 0) {
        charPaths.push_back("./RaylibTesting/Assets/3d_models/Players/PlayerOne.png");
        charPaths.push_back("./RaylibTesting/Assets/3d_models/Players/playerOne.iqm");
    }
    if (character == 1) {
        charPaths.push_back("./RaylibTesting/Assets/3d_models/Players/PlayerTwo.png");
        charPaths.push_back("./RaylibTesting/Assets/3d_models/Players/playerTwo.iqm");
    }
    if (character == 2) {
        charPaths.push_back("./RaylibTesting/Assets/3d_models/Players/PlayerThree.png");
        charPaths.push_back("./RaylibTesting/Assets/3d_models/Players/playerThree.iqm");
    }
    if (character == 3) {
        charPaths.push_back("./RaylibTesting/Assets/3d_models/Players/PlayerFour.png");
        charPaths.push_back("./RaylibTesting/Assets/3d_models/Players/playerFour.iqm");
    }
    return charPaths;
}



void Bomberman::createPlayer(Pos pos, int character) // extra argument
{
    EntityID id = _em->CreateNewEntity();
    // std::string playtex = "./RaylibTesting/Assets/3d_models/Players/PlayerFour.png";
    // std::string playermod = "./RaylibTesting/Assets/3d_models/Players/playerFour.iqm";
    // std::string playeranim = playermod;

    std::vector<std::string> paths = findCharPaths(character);

    // std::string skullmod = "RaylibTesting/Assets/3d_models/Guy/guy.iqm";
    // std::string modelAnimPath = "RaylibTesting/Assets/3d_models/Guy/guyanim.iqm";
    // std::string skulltex = "RaylibTesting/Assets/3d_models/Guy/guytex.png";

    
    _player.push_back(id);
    _em->Assign<Pos>(id, pos);
    _em->Assign<Velocity>(id, {0.08,0.08});
    _em->Assign<Input>(id, Input{NONE});
    _em->Assign<Score>(id, Score{0});
    _em->Assign<Health>(id, Health{100});
    _em->Assign<Skillset>(id, Skillset{0, 0, 1, false});
    _em->Assign<BombCapacity>(id, BombCapacity{3, 3});
    _em->Assign<CollisionObjectType>(id, CollisionObjectType{PLAYER});

    RL::Drawable3D *Player = new RL::Drawable3D(paths[0], paths[1], paths[1], RL::MODEL, 0.25);
    Player->setPosition((RL::Vector3f){
        translateFigureCoordinates(pos.x, _map->getMapWidth()),
        pos.y,
        translateFigureCoordinates(pos.y, _map->getMapDepth())
    });
    _em->Assign<Sprite>(id, Sprite{Player});
    _window->queueDrawable(Player);
}

void Bomberman::createAI(Pos pos, int character)
{
    EntityID id = _em->CreateNewEntity();
    // std::string aitex = "./RaylibTesting/Assets/3d_models/Players/PlayerFour.png";
    // std::string aimod = "./RaylibTesting/Assets/3d_models/Players/playerFour.iqm";

    std::vector<std::string> paths = findCharPaths(character);

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

    RL::Drawable3D *AI = new RL::Drawable3D(paths[0], paths[1], paths[1], RL::MODEL, 0.25);
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
}

void Bomberman::stopGameTimers()
{
    _gamePaused = true;
    _gameTimer.startPause();
}

bool Bomberman::checkIfVectorContain(std::vector<EntityID> vector, EntityID id) {
    if (std::find(vector.begin(), vector.end(), id) != vector.end())
        return true;
    return false;
}

// event as argument?
bool Bomberman::runFrame()
{
    _soundManager->updateMusicStream();
    _inputManager->popInputs();
    _inputManager->recordInputs();
    _event = _inputManager->getInputs();
    _aiBombLaying.clear();
  
    checkInput();
    checkBombalive();
    checkExplosionalive();
    for (std::shared_ptr<ISystem> system : _systems)
        system->update(_deltaTimer.returnTime(), _player, _aiBombLaying);
    for (EntityID id : _aiBombLaying) {
        if (checkIfVectorContain(_player, id))
            layBomb(id);
    }
    if (isGameEnd())
        return false;
    startDrawScene();
    _deltaTimer.restartTimer();
    return true;
}

void Bomberman::startDrawScene()
{
    _window->displayDrawable2D(_background);
    _window->displayDrawables(*_map.get());
    _window->clearWindow(BLACK);
    // _drawer->beginDrawing();
    // _drawer->clearBackground();
    // _drawer->begin3DMode(_window->getCamera());
}

void Bomberman::stopDrawScene()
{
    // _drawer->end3DMode();
    // // draw 2d elements (UI)
    // _drawer->endDrawing();
}

bool Bomberman::isGameEnd()
{
    for (EntityID id : _player) {
        if (id != INVALID_ENTITY)
            return false;
    }
    return true;
}
