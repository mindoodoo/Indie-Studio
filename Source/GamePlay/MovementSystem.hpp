/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** MovementSystem
*/

#ifndef MOVEMENTSYSTEM_HPP_
#define MOVEMENTSYSTEM_HPP_

#include "ISystem.hpp"
#include "../Map.hpp"

class MovementSystem : public ISystem {
    public:
        MovementSystem(std::shared_ptr<EntityManager> em, std::shared_ptr<RL::Map> map) : _map(map)
        {
            _em = em;
        };
        ~MovementSystem() {};

        void update(float deltaTime) override {
            for (EntityID ent : EntityViewer<Pos, Velocity, Input, Sprite>(*_em.get())) {
                Pos* playerPos = _em->Get<Pos>(ent);
                Velocity* playerVel = _em->Get<Velocity>(ent);
                Input* playerMovement = _em->Get<Input>(ent);
                Sprite* playerSprite = _em->Get<Sprite>(ent);

                switch (playerMovement->pressedKey) {
                    case UP:
                        moveUp(playerPos, (*playerVel) * deltaTime, playerSprite);
                        break;
                    case DOWN:
                        moveDown(playerPos, (*playerVel) * deltaTime, playerSprite);
                        break;
                    case LEFT:
                        moveLeft(playerPos, (*playerVel) * deltaTime, playerSprite);
                        break;
                    case RIGHT:
                        moveRight(playerPos, (*playerVel) * deltaTime, playerSprite);
                        break;
                }
            }
        };

        // check for collision with objects in other system
        void moveLeft(Pos *pos, Velocity vel, Sprite *playerSprite)
        {
            if (pos->x >= vel.x && _map->getParsedMap()[pos->y][pos->x - vel.x].tile == PATH) {
                pos->x -= vel.x;
                playerSprite->model.setPosition(pos->x, pos->y, pos->z);
            }
        };

        void moveRight(Pos *pos, Velocity vel, Sprite *playerSprite)
        {
            if (pos->x + vel.x < _map->getParsedMap()[pos->y].size() && _map->getParsedMap()[pos->y][pos->x + vel.x].tile == PATH) {
                pos->x += vel.x;
                playerSprite->model.setPosition(pos->x, pos->y, pos->z);
            }
        };

        void moveDown(Pos *pos, Velocity vel, Sprite *playerSprite)
        {
            if (pos->y >= vel.y && _map->getParsedMap()[pos->y - vel.y][pos->x].tile == PATH) {
                pos->y -= vel.y;
                playerSprite->model.setPosition(pos->x, pos->y, pos->z);
            }
        };

        void moveUp(Pos *pos, Velocity vel, Sprite *playerSprite)
        {
            if (pos->y + vel.y < _map->getParsedMap().size() && _map->getParsedMap()[pos->y + vel.y][pos->x].tile == PATH) {
                pos->y += vel.y;
                playerSprite->model.setPosition(pos->x, pos->y, pos->z);
            }
        };

    private:
        std::shared_ptr<RL::Map> _map;
};

#endif /* !MOVEMENTSYSTEM_HPP_ */
