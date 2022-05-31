/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** Bomberman
*/

#include "Bomberman.hpp"

Bomberman::Bomberman()
{
    _em = std::make_shared<EntityManager>();
    // take care with system order when adding to vector
    _systems.push_back(std::make_shared<MovementSystem>(_em, _map));
    createPlayer({5, 5});
}

Bomberman::~Bomberman()
{
}

void Bomberman::createPlayer(Pos pos)
{
    EntityID id = _em->CreateNewEntity();
    _player.push_back(id);
    _em->Assign<Pos>(id, pos);
    _em->Assign<Velocity>(id, {1,1});
    _em->Assign<Score>(id, Score{0});
    _em->Assign<Health>(id, Health{100});
}

void Bomberman::runFrame()
{
    float deltaTime = 0;
    while (_event != CLOSED_WINDOW) {
        // update deltatime
        for (std::shared_ptr<ISystem> system : _systems)
            system->update(deltaTime);
        // check for new events
    }
}

void Bomberman::checkGameEnd()
{
    
}
