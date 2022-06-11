/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** Bomberman
*/

#include "Bomberman.hpp"

Bomberman::Bomberman(std::shared_ptr<RL::Window> Window, std::shared_ptr<RL::InputManager> InputManager, std::shared_ptr<RL::Map> Map)
    : _window(Window), _map(Map), _inputManager(InputManager)
{
    _em = std::make_shared<EntityManager>();
    // take care with system order when adding to vector
    _systems.push_back(std::make_shared<MovementSystem>(_em, _map));
    _systems.push_back(std::make_shared<CollisionSystem>(_em, _map));
    _systems.push_back(std::make_shared<DrawSystem>(_em, _map));
    createPlayer({1, 1, 1});
    createItem({10, 10, 1});
    // createItem({5, 5, 1});
    //createBomb({5, 5, 1}, _player.back());
    //createMonster({5, 5, 1});
    createExplosion({1,1,1}, _player.back());
}

Bomberman::~Bomberman()
{
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
    std::string playtex = "./RaylibTesting/Assets/3d_models/Skull/Skull.png";
    std::string playermod = "./RaylibTesting/Assets/3d_models/Skull/mainplayerAnimated.glb";

    // std::string skullmod = "RaylibTesting/Assets/3d_models/Guy/guy.iqm";
    // std::string modelAnimPath = "RaylibTesting/Assets/3d_models/Guy/guyanim.iqm";
    // std::string skulltex = "RaylibTesting/Assets/3d_models/Guy/guytex.png";
    
    _player.push_back(id);
    _em->Assign<Pos>(id, pos);
    _em->Assign<Velocity>(id, {0.1,0.1});
    _em->Assign<Input>(id, Input{NONE});
    _em->Assign<Score>(id, Score{0});
    _em->Assign<Health>(id, Health{100});
    _em->Assign<Skillset>(id, Skillset{0, 0, 2, false});
    _em->Assign<BombCapacity>(id, BombCapacity{3, 3});
    _em->Assign<CollisionObjectType>(id, CollisionObjectType{PLAYER});
    RL::Drawable3D *Player = new RL::Drawable3D(playtex, playermod, "", RL::MODEL, 0.25);
    Player->setPosition((RL::Vector3f){
        translateFigureCoordinates(pos.x, _map->getMapWidth()),
        pos.y,
        translateFigureCoordinates(pos.y, _map->getMapDepth())
    });
    _em->Assign<Sprite>(id, Sprite{Player});
    _window->queueDrawable(Player);
}

void Bomberman::createItem(Pos pos)
{
    EntityID id = _em->CreateNewEntity();
    _em->Assign<Pos>(id, pos);
    _em->Assign<Skillset>(id, Skillset{0, 0, 5, false});
    _em->Assign<CollisionObjectType>(id, CollisionObjectType{ITEM});
    std::string speedUpPath = "./Source/PowerUps/Speed.png";
    RL::Drawable3D *speedUp = new RL::Drawable3D(speedUpPath, "", "", RL::POWER);
    speedUp->setPosition((RL::Vector3f){
        translateFigureCoordinates(pos.x, _map->getMapWidth()),
        1.0f,
        translateFigureCoordinates(pos.y, _map->getMapDepth())
    });
    _em->Assign<Sprite>(id, Sprite{speedUp});
    _window->queueDrawable(speedUp);
}

void Bomberman::createMonster(Pos pos)
{
    EntityID id = _em->CreateNewEntity();
    _em->Assign<Pos>(id, pos);
    _em->Assign<Velocity>(id, {0.1,0.1});
    _em->Assign<Score>(id, Score{0}); //defines how player score increases when killing monster
    _em->Assign<Health>(id, Health{100});
    _em->Assign<CollisionObjectType>(id, CollisionObjectType{MONSTER});
    // _em->Assign<Sprite>(id, Sprite{""});

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

void Bomberman::checkInput()
{
    Input* playerInput = _em->Get<Input>(_player.at(0));

    if (!_event.size())
        playerInput->pressedKey = NONE;

    for (int input : _event) {
        switch ((UserInput)input) {
            case UP:
            case DOWN:
            case LEFT:
            case RIGHT:
                playerInput->pressedKey = (UserInput)input;
                break;
           case LAY_BOMB:
               layBomb(_player[One]);
               break;
            default:
                playerInput->pressedKey = NONE;
        }
    }
}

void Bomberman::runFrame()
{
    _inputManager->recordInputs();
    _event = _inputManager->getInputs();
    float deltaTime = 1;
    while (_window->isWindowOpen()) {
        // update deltatime
        checkInput();

        for (std::shared_ptr<ISystem> system : _systems) {
            system->update(deltaTime, _player);
        }
        if (_player.size() <= 0)
            break;
        checkBombalive();
        checkExplosionalive();
        startDrawScene();
        _inputManager->popInputs();
        _inputManager->recordInputs();
        _event = _inputManager->getInputs();
    }
}

void Bomberman::startDrawScene()
{
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

void Bomberman::checkGameEnd()
{
    
}
