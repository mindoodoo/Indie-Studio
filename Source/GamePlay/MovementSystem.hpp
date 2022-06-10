/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** MovementSystem
*/

#ifndef MOVEMENTSYSTEM_HPP_
#define MOVEMENTSYSTEM_HPP_

#include "ISystem.hpp"
#include "../GameEngine/Map.hpp"
#include "../GameEngine/CollisionManager.hpp"
#include "../RaylibTypeEncaps.hpp"

class MovementSystem : public ISystem {
    public:
        MovementSystem(std::shared_ptr<EntityManager> em, std::shared_ptr<RL::Map> map) : _map(map)
        {
            _em = em;
        };
        ~MovementSystem() {};

        void update(float deltaTime, std::vector<EntityID> &playerIds) override {
            for (EntityID ent : EntityViewer<Pos, Velocity, Input, Sprite, CollisionObjectType>(*_em.get())) {
                Pos* playerPos = _em->Get<Pos>(ent);
                Velocity* playerVel = _em->Get<Velocity>(ent);
                Input* playerMovement = _em->Get<Input>(ent);
                Sprite* playerSprite = _em->Get<Sprite>(ent);
                CollisionObjectType* playerType = _em->Get<CollisionObjectType>(ent);
                Skillset skills({0, 0, 0, false});
                if (*playerType == PLAYER)
                    skills = *_em->Get<Skillset>(ent);
                Velocity vel = (*playerVel) * deltaTime + (skills.speedUp * 0.1);

                switch (playerMovement->pressedKey) {
                    case UP:
                        moveUp(playerPos, vel, playerSprite);
                        break;
                    case DOWN:
                        moveDown(playerPos, vel, playerSprite);
                        break;
                    case LEFT:
                        moveLeft(playerPos, vel, playerSprite);
                        break;
                    case RIGHT:
                        moveRight(playerPos, vel, playerSprite);
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

        bool checkMovable(Pos pos) {
            if (_colManager.collisionsWithWalls((RL::Vector3f){pos.x, pos.y, pos.z}, *_map.get()))
                return false;
            if (_colManager.collisionsWithCrates((RL::Vector3f){pos.x, pos.y, pos.z}, *_map.get()))
                return false;
            // also check for collision with other objects at that new position
            return true;
        }

        void moveLeft(Pos *pos, Velocity vel, Sprite *playerSprite)
        {
            float z = translatePosCoordinates(pos->y, _map->getMapDepth());
            if (pos->x >= vel.x && checkMovable({
                translatePosCoordinates(pos->x - vel.x, _map->getMapWidth()),
                0.5f + (z * 0.01f),
                z,
            })) {
                pos->x -= vel.x;
                playerSprite->model->setPosition((RL::Vector3f){pos->x, pos->y, pos->z});
                playerSprite->model->setRotation(270.0f);
            }
        };

        void moveRight(Pos *pos, Velocity vel, Sprite *playerSprite)
        {
            float z = translatePosCoordinates(pos->y, _map->getMapDepth());
            if (pos->x + vel.x < _map->getParsedMap()[pos->y].size() && checkMovable({
                translatePosCoordinates(pos->x + vel.x, _map->getMapWidth()),
                0.5f,
                z,
            })) {
                pos->x += vel.x;
                playerSprite->model->setPosition((RL::Vector3f){pos->x, pos->y, pos->z});
                playerSprite->model->setRotation(90.0f);
            }
        };

        void moveUp(Pos *pos, Velocity vel, Sprite *playerSprite)
        {
            float z = translatePosCoordinates(pos->y - vel.y, _map->getMapDepth());
            if (pos->y >= vel.y && checkMovable({
                translatePosCoordinates(pos->x, _map->getMapWidth()),
                0.5f + (z * 0.01f),
                z,
            })) {
                pos->y -= vel.y;
                playerSprite->model->setPosition((RL::Vector3f){pos->x, pos->y, pos->z});
                playerSprite->model->setRotation(180.0f);
            }
        };

        void moveDown(Pos *pos, Velocity vel, Sprite *playerSprite)
        {
            float z = translatePosCoordinates(pos->y + vel.y, _map->getMapDepth());
            if (pos->y + vel.y < _map->getParsedMap().size() && checkMovable({
                translatePosCoordinates(pos->x, _map->getMapWidth()),
                0.5f + (z * 0.01f),
                z,
            })) {
                pos->y += vel.y;
                playerSprite->model->setPosition((RL::Vector3f){pos->x, pos->y, pos->z});
                playerSprite->model->setRotation(0.0f);
            }
        };

    private:
        std::shared_ptr<RL::Map> _map;
        RL::CollisionManager _colManager;
};

#endif /* !MOVEMENTSYSTEM_HPP_ */
