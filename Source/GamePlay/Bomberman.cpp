/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** Bomberman
*/

#include "Bomberman.hpp"

Bomberman::Bomberman(std::shared_ptr<RL::Window> Window, std::shared_ptr<RL::InputManager> InputManager, std::shared_ptr<RL::Map> Map, std::shared_ptr<RL::Renderer> Drawer)
    : _window(Window), _map(Map), _drawer(Drawer), _inputManager(InputManager)
{
    _em = std::make_shared<EntityManager>();
    // take care with system order when adding to vector
    _systems.push_back(std::make_shared<MovementSystem>(_em, _map));
    _systems.push_back(std::make_shared<CollisionSystem>(_em, _map));
    _systems.push_back(std::make_shared<DrawSystem>(_em, _map, _drawer));
    createPlayer({5, 5});
}

Bomberman::~Bomberman()
{
}

void Bomberman::createPlayer(Pos pos)
{
    EntityID id = _em->CreateNewEntity();
    std::string skulltex = "./Source/3d_models/Skull_v3_L2.123c1407fc1e-ea5c-4cb9-9072-d28b8aba4c36/Skull.png";
    std::string skullmod = "./Source/3d_models/Skull_v3_L2.123c1407fc1e-ea5c-4cb9-9072-d28b8aba4c36/12140_Skull_v3_L2.obj";
    
    _player.push_back(id);
    _em->Assign<Pos>(id, pos);
    _em->Assign<Velocity>(id, {1,1});
    _em->Assign<Input>(id, Input{NONE});
    _em->Assign<Score>(id, Score{0});
    _em->Assign<Health>(id, Health{100});
    _em->Assign<Skillset>(id, Skillset{0, 0, 0, false});
    _em->Assign<BombCapacity>(id, BombCapacity{1, 1});
    _em->Assign<CollisionObjectType>(id, CollisionObjectType{PLAYER});
    RL::Drawable3D Skull = RL::Drawable3D(skulltex, skullmod, 0.04, RL::MODEL);
    Skull.setPosition(0, 1.0f, 0);
    _em->Assign<Sprite>(id, Sprite{Skull});
}

void Bomberman::createItem(Pos pos)
{
    EntityID id = _em->CreateNewEntity();
    _em->Assign<Pos>(id, pos);
    _em->Assign<Skillset>(id, Skillset{0, 0, 0, false});
    _em->Assign<CollisionObjectType>(id, CollisionObjectType{ITEM});
    // _em->Assign<Sprite>(id, Sprite{""});
}

void Bomberman::createMonster(Pos pos)
{
    EntityID id = _em->CreateNewEntity();
    _em->Assign<Pos>(id, pos);
    _em->Assign<Velocity>(id, {1,1});
    _em->Assign<Score>(id, Score{0}); //defines how player score increases when killing monster
    _em->Assign<Health>(id, Health{100});
    _em->Assign<CollisionObjectType>(id, CollisionObjectType{MONSTER});
    // _em->Assign<Sprite>(id, Sprite{""});
}

void Bomberman::createBomb(Pos pos, EntityID bombOwner)
{
    EntityID id = _em->CreateNewEntity();
    _em->Assign<Pos>(id, pos);
    _em->Assign<BombOwner>(id, BombOwner{bombOwner});
    _em->Assign<CollisionObjectType>(id, CollisionObjectType{BOMB});
    // _em->Assign<Sprite>(id, Sprite{""});
}

void Bomberman::checkInput()
{
    Input* playerInput = _em->Get<Input>(_player.at(0));
    switch (_event) {
        case UP:
        case DOWN:
        case LEFT:
        case RIGHT:
            playerInput->pressedKey = _event;
            break;
        default:
            playerInput->pressedKey = NONE;
    }
}

void Bomberman::runFrame()
{
    _event = (UserInput)_inputManager->recordInput();
    float deltaTime = 1;
    while (!WindowShouldClose()) {
    // while (_event != CLOSED_WINDOW) {
        // update deltatime
        checkInput();
        startDrawScene();
        for (std::shared_ptr<ISystem> system : _systems) {
            system->update(deltaTime);
        }
        stopDrawScene();
        _event = (UserInput)_inputManager->recordInput();
    }
}

void Bomberman::startDrawScene()
{
    _drawer->beginDrawing();
    _drawer->clearBackground();
    _drawer->begin3DMode(_window->getCamera());
}

void Bomberman::stopDrawScene()
{
    _drawer->end3DMode();
    // draw 2d elements (UI)
    _drawer->endDrawing();
}

void Bomberman::checkGameEnd()
{
    
}
