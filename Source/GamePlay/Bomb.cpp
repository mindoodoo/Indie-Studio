/*
** EPITECH PROJECT, 2022
** .
** File description:
** .
*/

#include "Bomberman.hpp"

void Bomberman::layBomb(EntityID playerid)
{
    std::cout << _em->Get<BombCapacity>(playerid)->curCapacity << std::endl;
    std::cout << "LAYING bomb" << std::endl;
    if (_em->Get<BombCapacity>(playerid)->curCapacity >= 1) {
        createBomb(*_em->Get<Pos>(playerid), _player[One]);
        _em->Get<BombCapacity>(playerid)->curCapacity -= 1;
    }
}

void Bomberman::checkBombalive() {
    for (EntityID ent: EntityViewer<CollisionObjectType, Timer>(*_em.get())) {
        if (*_em->Get<CollisionObjectType>(ent) == BOMB) {
            if (_em->Get<Timer>(ent)->returnTime() >= 3) {
                //TODO REMOVE BOMB
                for (EntityID ent: EntityViewer<BombCapacity>(*_em.get())) {
                    _em->Get<BombCapacity>(ent)->curCapacity += 1;
                }
                std::cout << "BOOOM" << std::endl;
                _em->DestroyEntity(ent);
            }

        }
    }
}