/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** Bomberman
*/

#include "Bomberman.hpp"

Bomberman::Bomberman(std::shared_ptr<RL::Window> Window, std::shared_ptr<RL::InputManager> InputManager, std::shared_ptr<RL::Map> Map, std::shared_ptr<RL::SoundManager> SoundManager, std::shared_ptr<RL::SaveManager> SaveManager, std::vector<PlayerChoice> playerChoices, bool coinMode)
    : _window(Window), _map(Map), _inputManager(InputManager), _soundManager(SoundManager), _background("./RaylibTesting/Assets/Background/background1.png"), _layout("./Source/PowerUps/Layout_Small.png"), _saveManager(SaveManager), _uiManager(Window)
{
    _background.resize(_window->getDimensions());
    _layout.resize({_window->getDimensions().x, 150});
    _em = std::make_shared<EntityManager>();
    _maxGameTime = 180;
    _coinMode = coinMode;
    _maxCoins = 0;

    // Take care with system order when adding to vector
    _systems.push_back(std::make_shared<CollisionSystem>(_em, _window, _soundManager, _map, coinMode));
    _systems.push_back(std::make_shared<MovementSystem>(_em, _map, _inputManager));
    _systems.push_back(std::make_shared<AISystem>(_em, _map));
    _systems.push_back(std::make_shared<DrawSystem>(_em, _map));

    _allModels.push_back(RL::Drawable3D("./RaylibTesting/Assets/Bomb/bombModified.png", "./RaylibTesting/Assets/Bomb/Bomb.obj", "", RL::MODEL, 2));
    _allModels.push_back(RL::Drawable3D("./RaylibTesting/Assets/Explosion/textures/fire.png", "./RaylibTesting/Assets/Explosion/textures/fire.iqm", "./RaylibTesting/Assets/Explosion/textures/fire.iqm", RL::MODEL, 3));
    _allModels.push_back(RL::Drawable3D("./RaylibTesting/Assets/Coin/coin.png", "./RaylibTesting/Assets/Coin/coin.obj", "", RL::COIN, 1));

    _allIcons.push_back(new RL::Drawable2D("./RaylibTesting/Assets/2d_models/iconOne.png"));
    _allIcons.push_back(new RL::Drawable2D("./RaylibTesting/Assets/2d_models/iconTwo.png"));
    _allIcons.push_back(new RL::Drawable2D("./RaylibTesting/Assets/2d_models/iconThree.png"));
    _allIcons.push_back(new RL::Drawable2D("./RaylibTesting/Assets/2d_models/iconFour.png"));

    float windowPercentageShift = _window->getDimensions().x * 25 / 100;
    std::vector<float> windowPercentageOffsetIcon = {
        float(_window->getDimensions().x * 18 / 100),
        float(_window->getDimensions().x * 18 / 100),
        float(_window->getDimensions().x * 2 / 100),
        float(_window->getDimensions().x * 2 / 100)};
    std::vector<float> windowPercentageOffsetPowerUp = {
        float(_window->getDimensions().x * 10.2 / 100),
        float(_window->getDimensions().x * 10.2 / 100),
        float(_window->getDimensions().x * 2.3 / 100),
        float(_window->getDimensions().x * 2.3 / 100)};

    for ( int i = 0; i < _allIcons.size(); i++ ){
        _allIcons[playerChoices[i].Character]->resize({60,60});
        _allIcons[playerChoices[i].Character]->setPosition((i * windowPercentageShift) + (windowPercentageOffsetIcon[i]), 15, 0);
        _window->queueDrawable(_allIcons[i]);
    }

    //this is respndible for the music being played then shuffle enabled, comment out to cancel
    //_soundManager->playRandomMusic();
    _soundManager->playSpecificMusic("BackgroundMusicOne");
    _soundManager->enableDisableShuffle();

    std::vector<Pos>playerStartPositions;
    playerStartPositions.push_back({13, 11, 1});
    playerStartPositions.push_back({1, 1, 1});
    playerStartPositions.push_back({13, 1, 1});
    playerStartPositions.push_back({1, 11, 1});

    //Check if loading game or not
    if (!_saveManager->getLoading()) {
        _maxGameTime = _saveManager->getTime();
        int count = 0;
        UIPos uiPos;
        for (int x = 0; x < _saveManager->getPlayers().size(); x++) {
            uiPos = {int((x * windowPercentageShift) + (windowPercentageOffsetPowerUp[x]) + 65), 5};
            createPlayerLoadGame(_saveManager->getPlayerPos(x), _saveManager->getSkillsetPlayer(x),
                                 _saveManager->getScorePlayer(x), _saveManager->getBombcapPlayer(x), playerChoices[x].Character, uiPos);
            count++;
        }
        if (_saveManager->getPlayers().size() >= 1) {
            _player.push_back(INVALID_ENTITY);
        }
        for (int x = 0; x < _saveManager->getAIs().size(); x++) {
            uiPos = {int((count * windowPercentageShift) + (windowPercentageOffsetPowerUp[count]) + 65), 5};
            createAILoadGame(_saveManager->getAIPos(x), _saveManager->getSkillsetAI(x), _saveManager->getScoreAI(x),
                             _saveManager->getBombcapAI(x), playerChoices[count].Character, uiPos);
            count++;
        }

        for (int x = 0; x < _saveManager->getItems().size(); x++)
            generateItemsLoadGame(_saveManager->getItemPos(x), _saveManager->getSkillsetItem(x));

        generateItems(0);
        for (int x = 0; x < _saveManager->getBombs().size(); x++)
            createBomb(_saveManager->getBombPos(x), {EntityID(x)},_saveManager->getSkillsetBomb(x), _saveManager->getBombTime(x));

        for (int x = 0; x < _saveManager->getExplosions().size(); x++)
            createExplosion(_saveManager->getExploPos(x), {EntityID(x)}, _saveManager->getExploTime(x));

        _gamePaused = false;
        _gameTimer.startTimer();
        _deltaTimer.startTimer();

    } else {
        _maxGameTime = 180;
        for (int i = 0 ; i < playerChoices.size(); i++) {
            UIPos uiPos = {int((i * windowPercentageShift) + (windowPercentageOffsetPowerUp[i]) + 65), 5};
            if (playerChoices[i].CPU == false) 
                createPlayer(playerStartPositions[i], playerChoices[i].Character, uiPos);
            else {
                if (i == 1)
                    _player.push_back(INVALID_ENTITY);
                createAI(playerStartPositions[i], playerChoices[i].Character, uiPos);

            }
        }
        if (coinMode)
            generateCoins();
        else
            generateItems(1);
        _gamePaused = false;
        _gameTimer.startTimer();
        _deltaTimer.startTimer();
    }
    _gamePaused = false;
    this->_pauseGame = false;
}

Bomberman::~Bomberman()
{
}



void Bomberman::generateItemsLoadGame(Pos pos, Skillset skill)
{
    if (skill.wallPass)
        createWallPassItem(pos, false);
    if (skill.bombUp >= 1)
        createBombUpItem(pos, false);
    if (skill.speedUp >= 1)
        createSpeedUpItem(pos, false);
    if (skill.fireUp >= 1)
        createFireUpItem(pos, false);

}

void Bomberman::generateItems(int wallPassAmount)
{
    int placeItem;

    for (int i = 0; i < _map->getMapDepth(); i++) {
        for (int j = 0; j < _map->getMapWidth(); j++) {
            if (_map->getParsedMap()[i][j].tile == 2) {
                placeItem = rand() % 100;
                if (placeItem > 77) {
                    switch (rand() % 4) {
                        case 0:
                            createSpeedUpItem({(float)j, (float)i, 1}, true);
                            break;
                        case 1:
                            createBombUpItem({(float)j, (float)i, 1}, true);
                            break;
                        case 2:
                            createFireUpItem({(float)j, (float)i, 1}, true);
                            break;
                        case 3:
                            if (wallPassAmount) {
                                wallPassAmount--;
                                createWallPassItem({(float)j, (float)i, 1}, true);
                            }
                            break;
                    }
                }
            }
        }
    }
}

void Bomberman::generateCoins()
{
    int placeItem;

    for (int i = 0; i < _map->getMapDepth(); i++) {
        for (int j = 0; j < _map->getMapWidth(); j++) {
            if (_map->getParsedMap()[i][j].tile == 2) {
                placeItem = rand() % 100;
                if (placeItem > 77) {
                    createCoin({(float)j, (float)i, 1});
                    _maxCoins++;
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

void Bomberman::createCoin(Pos pos)
{
    EntityID id = _em->CreateNewEntity();
    _em->Assign<Pos>(id, pos);
    _em->Assign<Score>(id, Score{1});
    _em->Assign<CollisionObjectType>(id, CollisionObjectType{ITEM});
    RL::Drawable3D *coin = makeDrawable3DPointer(_allModels[2], RL::COIN);
    coin->setRotation(90);
    coin->resize(0.3);
    coin->setPosition((RL::Vector3f){
        translateFigureCoordinates(pos.x, _map->getMapWidth()),
        1.0f,
        translateFigureCoordinates(pos.y, _map->getMapDepth())
    });
    coin->setHidden(true);
    _em->Assign<Sprite>(id, Sprite{coin});
    _window->queueDrawable(coin);
}

void Bomberman::createPlayer(Pos pos, int character, UIPos uiPos) // extra argument
{
    EntityID id = _em->CreateNewEntity();
    // std::string playtex = "./RaylibTesting/Assets/3d_models/Players/PlayerFour.png";
    // std::string playermod = "./RaylibTesting/Assets/3d_models/Players/playerFour.iqm";
    // std::string playeranim = playermod;

    std::vector<std::string> paths = findCharPaths(character);

    _player.push_back(id);
    _em->Assign<Pos>(id, pos);
    _em->Assign<UIPos>(id, uiPos);
    _em->Assign<UiContinue>(id, {(character <= 1 ? false : true)});
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
        0.5f,
        translateFigureCoordinates(pos.y, _map->getMapDepth())
    });
    _em->Assign<Sprite>(id, Sprite{Player});
    _window->queueDrawable(Player);
}

void Bomberman::createUIPowerIconsForPlayer(Skillset skill, UIPos uiPos, bool continueToRight)
{
    for (int i = 1; i <= skill.bombUp; i++)
        _uiManager.createBombUp(uiPos, i, continueToRight);

    for (int i = 1; i <= skill.speedUp; i++)
        _uiManager.createSpeedUp(uiPos, i, continueToRight);

    for (int i = 2; i <= skill.fireUp; i++)
        _uiManager.createFireUp(uiPos, i, continueToRight);

    if (skill.wallPass)
        _uiManager.createWallPass(uiPos);
}


void Bomberman::createPlayerLoadGame(Pos pos, Skillset skill, int score, BombCapacity capa, int character, UIPos uiPos)
{
    std::vector<std::string> paths = findCharPaths(character);

    EntityID id = _em->CreateNewEntity();
    _player.push_back(id);
    _em->Assign<Pos>(id, pos);
    _em->Assign<UIPos>(id, uiPos);
    createUIPowerIconsForPlayer(skill, uiPos, {(character <= 1 ? false : true)});
    _em->Assign<UiContinue>(id, {(character <= 1 ? false : true)});
    _em->Assign<Velocity>(id, {0.08,0.08});
    _em->Assign<Input>(id, Input{NONE});
    _em->Assign<Score>(id, {std::size_t (score)});
    _em->Assign<Health>(id, Health{100});
    _em->Assign<Skillset>(id, skill);
    _em->Assign<BombCapacity>(id, capa);
    _em->Assign<CollisionObjectType>(id, CollisionObjectType{PLAYER});

    RL::Drawable3D *Player = new RL::Drawable3D(paths[0], paths[1], paths[1], RL::MODEL, 0.25);
    Player->setPosition((RL::Vector3f){
            translateFigureCoordinates(pos.x, _map->getMapWidth()),
            0.5f,
            translateFigureCoordinates(pos.y, _map->getMapDepth())
    });
    _em->Assign<Sprite>(id, Sprite{Player});
    _window->queueDrawable(Player);
}

void Bomberman::createAILoadGame(Pos pos, Skillset skill, int score, BombCapacity capa, int character, UIPos uiPos)
{
    EntityID id = _em->CreateNewEntity();
    std::vector<std::string> paths = findCharPaths(character);

    _player.push_back(id);
    _em->Assign<Pos>(id, pos);
    _em->Assign<UIPos>(id, uiPos);
    _em->Assign<UiContinue>(id, {(character <= 1 ? false : true)});
    createUIPowerIconsForPlayer(skill, uiPos, {(character <= 1 ? false : true)});
    _em->Assign<Velocity>(id, {0.04,0.04});
    _em->Assign<Input>(id, Input{NONE});
    _em->Assign<Score>(id, {std::size_t(score)});
    _em->Assign<Health>(id, Health{100});
    _em->Assign<Skillset>(id, skill);
    _em->Assign<BombCapacity>(id, capa);
    _em->Assign<CollisionObjectType>(id, CollisionObjectType{AI});

    AIData data = {false, {0, 0, 0}, RANDOM, 5, {}, {1, 2}};
    _em->Assign<AIData>(id, data);

    RL::Drawable3D *AI = new RL::Drawable3D(paths[0], paths[1], paths[1], RL::MODEL, 0.25);
    AI->setPosition((RL::Vector3f){
            translateFigureCoordinates(pos.x, _map->getMapWidth()),
            0.5f,
            translateFigureCoordinates(pos.y, _map->getMapDepth())
    });
    _em->Assign<Sprite>(id, Sprite{AI});
    _window->queueDrawable(AI);

}

void Bomberman::createAI(Pos pos, int character, UIPos uiPos)
{
    EntityID id = _em->CreateNewEntity();
    // std::string aitex = "./RaylibTesting/Assets/3d_models/Players/PlayerFour.png";
    // std::string aimod = "./RaylibTesting/Assets/3d_models/Players/playerFour.iqm";

    std::vector<std::string> paths = findCharPaths(character);

    _player.push_back(id);
    _em->Assign<Pos>(id, pos);
    _em->Assign<UIPos>(id, uiPos);
    _em->Assign<UiContinue>(id, {(character <= 1 ? false : true)});
    _em->Assign<Velocity>(id, {0.08,0.08});
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
        0.5f,
        translateFigureCoordinates(pos.y, _map->getMapDepth())
    });
    _em->Assign<Sprite>(id, Sprite{AI});
    _window->queueDrawable(AI);
}

void Bomberman::createSpeedUpItem(Pos pos, bool hidden)
{
    EntityID id = _em->CreateNewEntity();
    _em->Assign<Pos>(id, pos);
    _em->Assign<Skillset>(id, Skillset{0, 1, 0, false});
    _em->Assign<CollisionObjectType>(id, CollisionObjectType{ITEM});
    _em->Assign<ItemType>(id, ItemType{SPEED_UP});
    std::string speedUpPath = "./Source/PowerUps/SpeedFlipped.png";
    RL::Drawable3D *speedUp = new RL::Drawable3D(speedUpPath, "", "", RL::POWER);
    speedUp->setPosition((RL::Vector3f){
        translateFigureCoordinates(pos.x, _map->getMapWidth()),
        1.0f,
        translateFigureCoordinates(pos.y, _map->getMapDepth())
    });
    speedUp->setHidden(hidden);
    _em->Assign<Sprite>(id, Sprite{speedUp});
    _window->queueDrawable(speedUp);
}

void Bomberman::createBombUpItem(Pos pos, bool hidden)
{
    EntityID id = _em->CreateNewEntity();
    _em->Assign<Pos>(id, pos);
    _em->Assign<Skillset>(id, Skillset{1, 0, 0, false});
    _em->Assign<CollisionObjectType>(id, CollisionObjectType{ITEM});
    _em->Assign<ItemType>(id, ItemType{BOMB_UP});
    std::string bombUpPath = "./Source/PowerUps/BombUpFlipped.png";
    RL::Drawable3D *bombUp = new RL::Drawable3D(bombUpPath, "", "", RL::POWER);
    bombUp->setPosition((RL::Vector3f){
        translateFigureCoordinates(pos.x, _map->getMapWidth()),
        1.0f,
        translateFigureCoordinates(pos.y, _map->getMapDepth())
    });
    bombUp->setHidden(hidden);
    _em->Assign<Sprite>(id, Sprite{bombUp});
    _window->queueDrawable(bombUp);
}

void Bomberman::createFireUpItem(Pos pos, bool hidden)
{
    EntityID id = _em->CreateNewEntity();
    _em->Assign<Pos>(id, pos);
    _em->Assign<Skillset>(id, Skillset{0, 0, 1, false});
    _em->Assign<CollisionObjectType>(id, CollisionObjectType{ITEM});
    _em->Assign<ItemType>(id, ItemType{FIRE_UP});
    std::string fireUpPath = "./Source/PowerUps/PowerUpFlipped.png";
    RL::Drawable3D *fireUp = new RL::Drawable3D(fireUpPath, "", "", RL::POWER);
    fireUp->setPosition((RL::Vector3f){
        translateFigureCoordinates(pos.x, _map->getMapWidth()),
        1.0f,
        translateFigureCoordinates(pos.y, _map->getMapDepth())
    });
    fireUp->setHidden(hidden);
    _em->Assign<Sprite>(id, Sprite{fireUp});
    _window->queueDrawable(fireUp);
}

void Bomberman::createWallPassItem(Pos pos, bool hidden)
{
    EntityID id = _em->CreateNewEntity();
    _em->Assign<Pos>(id, pos);
    _em->Assign<Skillset>(id, Skillset{0, 0, 0, true});
    _em->Assign<CollisionObjectType>(id, CollisionObjectType{ITEM});
    _em->Assign<ItemType>(id, ItemType{WALLPASS});
    std::string wallPassPath = "./Source/PowerUps/WallsWalkableFlipped.png";
    RL::Drawable3D *wallPass = new RL::Drawable3D(wallPassPath, "", "", RL::POWER);
    wallPass->setPosition((RL::Vector3f){
        translateFigureCoordinates(pos.x, _map->getMapWidth()),
        1.0f,
        translateFigureCoordinates(pos.y, _map->getMapDepth())
    });
    wallPass->setHidden(hidden);
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
        0.5f,
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
        system->update(_deltaTimer.returnTime(), _player, _aiBombLaying, _deadPlayers, _maxCoins);
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

int Bomberman::getTimeasInt()
{
    return _maxGameTime - _gameTimer.returnTime();
}

std::string Bomberman::getGameTime()
{
    int leftTime = _maxGameTime - _gameTimer.returnTime();

    int minutes = leftTime / 60;
    int seconds = leftTime % 60;
    std::string timeString = std::to_string(minutes) + " : ";
    if (seconds < 10)
        timeString += "0" + std::to_string(seconds);
    else
        timeString += std::to_string(seconds);
    return timeString;
}

void Bomberman::startDrawScene()
{
    _window->displayDrawable2D(_background);
    _window->displayDrawable2D(_layout);
    _window->displayDrawables(*_map.get(), getGameTime(), _window->getDimensions().x / 2 - 45, 110);
    _window->clearWindow(BLACK);
}

void Bomberman::stopDrawScene()
{
}

std::vector<std::size_t> Bomberman::getDeadPlayers()
{
    return _deadPlayers;
}

void Bomberman::addRemainingPlayer()
{
    for(int i = 0; i < _player.size(); i++) {
        if (_player[i] != INVALID_ENTITY) {
            _deadPlayers.push_back(GetEntityIndex(_player[i]));
        }
    }
}

bool Bomberman::isGameEnd()
{
    if (_maxGameTime - _gameTimer.returnTime() < 0)
        return true;
    if (_coinMode && !_maxCoins)
        return true;
    int playerCount = 0;
    int aiCount = 0;
    
    for (EntityID ent : EntityViewer<CollisionObjectType>(*_em.get())) {
        if (*_em->Get<CollisionObjectType>(ent) == AI)
            aiCount++;
        if (*_em->Get<CollisionObjectType>(ent) == PLAYER)
            playerCount++;

    }
    if (playerCount == 0) {
        addRemainingPlayer();
        return true;
    }
    if (aiCount == 0 && playerCount <= 1) {
        addRemainingPlayer();
        return true;
    }
    return false;
}


std::shared_ptr <EntityManager> Bomberman::getEm()
{
    return _em;
}