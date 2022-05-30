/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "../ECS/EntityManager.hpp"
#include "Components.hpp"

class Player {
    public:
        Player(std::shared_ptr<EntityManager> em, Pos pos);
        ~Player();

        void movePlayer(UserInput event, Map map);

        // move function need collision detection as well (monster + items)
        void moveLeft(Map map);
        void moveRight(Map map);
        void moveUp(Map map);
        void moveDown(Map map);

    private:
        EntityID _id;
        std::shared_ptr<EntityManager> _em;
};

#endif /* !PLAYER_HPP_ */
