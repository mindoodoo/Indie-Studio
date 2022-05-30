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
    _player.push_back(Player(_em, Pos{5, 5}));
}

Bomberman::~Bomberman()
{
}

void Bomberman::runFrame()
{
    while (_event != CLOSED_WINDOW) {
        for (Player player : _player)
            player.movePlayer(_event, _map);
        // check for new events
    }
}

void Bomberman::checkGameEnd()
{
    
}
