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
#include "../CollisionManager.hpp"

class MovementSystem : public ISystem {
    public:
        MovementSystem(std::shared_ptr<EntityManager> em, std::shared_ptr<RL::Map> map) : _map(map)
        {
            _em = em;
        };
        ~MovementSystem() {};

        void update(float deltaTime, std::vector<EntityID> &playerIds) override {
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

        float translatePosCoordinates(float pos, int borderSize)
        {
            float newpos = pos - (borderSize / 2);
            if (borderSize % 2 == 0)
                newpos += 0.5;
            return newpos;
        }

        // check for collision with objects in other system
        void moveLeft(Pos *pos, Velocity vel, Sprite *playerSprite)
        {
            float z = translatePosCoordinates(pos->y, _map->getMapDepth());
            if (pos->x >= vel.x && !_colManager.collisionsWithWalls({
                translatePosCoordinates(pos->x - vel.x, _map->getMapWidth()),
                0.5f + (z * 0.01f),
                z,
            }, *_map.get())) {
                pos->x -= vel.x;
                playerSprite->model.setPosition(pos->x, pos->y, pos->z);
            }
        };

        void moveRight(Pos *pos, Velocity vel, Sprite *playerSprite)
        {
            float z = translatePosCoordinates(pos->y, _map->getMapDepth());
            if (pos->x + vel.x < _map->getParsedMap()[pos->y].size() && !_colManager.collisionsWithWalls({
                translatePosCoordinates(pos->x + vel.x, _map->getMapWidth()),
                0.5f + (z * 0.01f),
                z,
            }, *_map.get())) {
                pos->x += vel.x;
                playerSprite->model.setPosition(pos->x, pos->y, pos->z);
            }
        };

        void moveUp(Pos *pos, Velocity vel, Sprite *playerSprite)
        {
            float z = translatePosCoordinates(pos->y - vel.y, _map->getMapDepth());
            if (pos->y >= vel.y && !_colManager.collisionsWithWalls({
                translatePosCoordinates(pos->x, _map->getMapWidth()),
                0.5f + (z * 0.01f),
                z,
            }, *_map.get())) {
                pos->y -= vel.y;
                playerSprite->model.setPosition(pos->x, pos->y, pos->z);
            }
        };

        void moveDown(Pos *pos, Velocity vel, Sprite *playerSprite)
        {
            float z = translatePosCoordinates(pos->y + vel.y, _map->getMapDepth());
            if (pos->y + vel.y < _map->getParsedMap().size() && !_colManager.collisionsWithWalls({
                translatePosCoordinates(pos->x, _map->getMapWidth()),
                0.5f + (z * 0.01f),
                z,
            }, *_map.get())) {
                pos->y += vel.y;
                playerSprite->model.setPosition(pos->x, pos->y, pos->z);
            }
        };

    private:
        std::shared_ptr<RL::Map> _map;
        RL::CollisionManager _colManager;
};

#endif /* !MOVEMENTSYSTEM_HPP_ */
