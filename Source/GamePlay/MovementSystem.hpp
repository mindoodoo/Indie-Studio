/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** MovementSystem
*/

#ifndef MOVEMENTSYSTEM_HPP_
#define MOVEMENTSYSTEM_HPP_

#include "ISystem.hpp"

class MovementSystem : public ISystem {
    public:
        MovementSystem(std::shared_ptr<EntityManager> em, Map map) {
            _em = em;
            _map = map;
        };
        ~MovementSystem() {};

        void update(float deltaTime) override {
            for (EntityID ent : EntityViewer<Pos, Velocity, Input>(*_em.get())) {
                Pos* playerPos = _em->Get<Pos>(ent);
                Velocity* playerVel = _em->Get<Velocity>(ent);
                Input* playerMovement = _em->Get<Input>(ent);

                switch (playerMovement->pressedKey) {
                    case UP:
                        moveUp(playerPos, (*playerVel) * deltaTime);
                        break;
                    case DOWN:
                        moveDown(playerPos, (*playerVel) * deltaTime);
                        break;
                    case LEFT:
                        moveLeft(playerPos, (*playerVel) * deltaTime);
                        break;
                    case RIGHT:
                        moveRight(playerPos, (*playerVel) * deltaTime);
                        break;
                }
            }
        };

        // check for collision with objects in other system
        void moveLeft(Pos *pos, Velocity vel)
        {
            if (pos->x >= vel.x && _map.map[pos->y][pos->x - vel.x] == PATH)
                pos->x -= vel.x;
        };

        void moveRight(Pos *pos, Velocity vel)
        {
            if (pos->x + vel.x < _map.map[pos->y].size() && _map.map[pos->y][pos->x + vel.x] == PATH)
                pos->x += vel.x;
        };

        void moveUp(Pos *pos, Velocity vel)
        {
            if (pos->y >= vel.y && _map.map[pos->y - vel.y][pos->x] == PATH)
                pos->y -= vel.y;
        };

        void moveDown(Pos *pos, Velocity vel)
        {
            if (pos->y + vel.y < _map.map.size() && _map.map[pos->y + vel.y][pos->x] == PATH)
                pos->y += vel.y;
        };

    private:
        Map _map;
};

#endif /* !MOVEMENTSYSTEM_HPP_ */
