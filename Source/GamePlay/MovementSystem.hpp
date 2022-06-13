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
#include "../Raylib/InputManager.hpp"

class MovementSystem : public ISystem {
    public:
        enum PlayerType {
            Player_One,
            Player_Two,
            Other
        };
        MovementSystem(std::shared_ptr<EntityManager> em, std::shared_ptr<RL::Map> map, std::shared_ptr<RL::InputManager> iM) : _map(map), _inputManager(iM)
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
                bool wallPass = false;
                if (*playerType == PLAYER) {
                    if (ent == playerIds[0])
                        type = Player_One;
                    else if (ent == playerIds[1])
                        type = Player_Two;
                    else
                        type = Other;
                    skills = *_em->Get<Skillset>(ent);
                    wallPass = skills.wallPass;
                }
                Velocity vel = (*playerVel) * (deltaTime * 1000) + (skills.speedUp * 0.04);

                switch (playerMovement->pressedKey) {
                    case UP:
                    case UP2:
                        moveUp(playerPos, vel, playerSprite, wallPass);
                        break;
                    case DOWN:
                    case DOWN2:
                        moveDown(playerPos, vel, playerSprite, wallPass);
                        break;
                    case LEFT:
                    case LEFT2:
                        moveLeft(playerPos, vel, playerSprite,wallPass);
                        break;
                    case RIGHT:
                    case RIGHT2:
                        moveRight(playerPos, vel, playerSprite, wallPass);
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

        bool checkMovable(Pos pos, bool wallPass) {
            if (_colManager.collisionsWithWalls((RL::Vector3f){pos.x, pos.y, pos.z}, *_map.get()))
                return false;
            if (!wallPass && _colManager.collisionsWithCrates((RL::Vector3f){pos.x, pos.y, pos.z}, *_map.get()))
                return false;
            return true;
        }

        void moveLeft(Pos *pos, Velocity vel, Sprite *playerSprite, bool wallPass)
        {
            if (_inputManager->playerHasPressedKeyAsChar(type != Player_Two ? UP : UP2)) {
                moveUpLeft(pos, vel, playerSprite, wallPass);
                return;
            }
            if (_inputManager->playerHasPressedKeyAsChar(type != Player_Two ? DOWN : DOWN2)) {
                moveDownLeft(pos, vel, playerSprite, wallPass);
                return;
            }
            float z = translatePosCoordinates(pos->y, _map->getMapDepth());
            if (pos->x >= vel.x && checkMovable({
                translatePosCoordinates(pos->x - vel.x, _map->getMapWidth()),
                0.5f + (z * 0.01f),
                z,
            }, wallPass)) {
                pos->x -= vel.x;
                playerSprite->model->setPosition((RL::Vector3f){pos->x, pos->y, pos->z});
                playerSprite->model->setRotation(270.0f);
            }
        };

        void moveRight(Pos *pos, Velocity vel, Sprite *playerSprite, bool wallPass)
        {
            if (_inputManager->playerHasPressedKeyAsChar(type != Player_Two ? UP : UP2)) {
                moveUpRight(pos, vel, playerSprite, wallPass);
                return;
            }
            if (_inputManager->playerHasPressedKeyAsChar(type != Player_Two ? DOWN : DOWN2)) {
                moveDownRight(pos, vel, playerSprite, wallPass);
                return;
            }
            float z = translatePosCoordinates(pos->y, _map->getMapDepth());
            if (pos->x + vel.x < _map->getParsedMap()[pos->y].size() && checkMovable({
                translatePosCoordinates(pos->x + vel.x, _map->getMapWidth()),
                0.5f,
                z,
            }, wallPass)) {
                pos->x += vel.x;
                playerSprite->model->setPosition((RL::Vector3f){pos->x, pos->y, pos->z});
                playerSprite->model->setRotation(90.0f);
            }
        };

        void moveUp(Pos *pos, Velocity vel, Sprite *playerSprite, bool wallPass)
        {
            if (_inputManager->playerHasPressedKeyAsChar(type != Player_Two ? LEFT : LEFT2)) {
                moveUpLeft(pos, vel, playerSprite, wallPass);
                return;
            }
            if (_inputManager->playerHasPressedKeyAsChar(type != Player_Two ? RIGHT : RIGHT2)) {
                moveUpRight(pos, vel, playerSprite, wallPass);
                return;
            }
            float z = translatePosCoordinates(pos->y - vel.y, _map->getMapDepth());
            if (pos->y >= vel.y && checkMovable({
                translatePosCoordinates(pos->x, _map->getMapWidth()),
                0.5f + (z * 0.01f),
                z,
            }, wallPass)) {
                pos->y -= vel.y;
                playerSprite->model->setPosition((RL::Vector3f){pos->x, pos->y, pos->z});
                playerSprite->model->setRotation(180.0f);
            }
        };

        void moveDown(Pos *pos, Velocity vel, Sprite *playerSprite, bool wallPass)
        {
            if (_inputManager->playerHasPressedKeyAsChar(type != Player_Two ? LEFT : LEFT2)) {
                moveDownLeft(pos, vel, playerSprite, wallPass);
                return;
            }
            if (_inputManager->playerHasPressedKeyAsChar(type != Player_Two ? RIGHT : RIGHT2)) {
                moveDownRight(pos, vel, playerSprite, wallPass);
                return;
            }
            float z = translatePosCoordinates(pos->y + vel.y, _map->getMapDepth());
            if (pos->y + vel.y < _map->getParsedMap().size() && checkMovable({
                translatePosCoordinates(pos->x, _map->getMapWidth()),
                0.5f + (z * 0.01f),
                z,
            }, wallPass)) {
                pos->y += vel.y;
                playerSprite->model->setPosition((RL::Vector3f){pos->x, pos->y, pos->z});
                playerSprite->model->setRotation(0.0f);
            }
        };

        void moveUpLeft(Pos *pos, Velocity vel, Sprite *playerSprite, bool wallPass)
        {
            float z = translatePosCoordinates(pos->y - (vel.y / 2), _map->getMapDepth());
            if (pos->x >= vel.x && pos->y >= vel.y && checkMovable({
                translatePosCoordinates(pos->x - (vel.x / 2), _map->getMapWidth()),
                0.5f + (z * 0.01f),
                z,
            }, wallPass)) {
                pos->x -= vel.x / 2;
                pos->y -= vel.y / 2;
                playerSprite->model->setPosition((RL::Vector3f){pos->x, pos->y, pos->z});
                playerSprite->model->setRotation(225.0f);
            }
        };

        void moveUpRight(Pos *pos, Velocity vel, Sprite *playerSprite, bool wallPass)
        {
            float z = translatePosCoordinates(pos->y - (vel.y / 2), _map->getMapDepth());
            if (pos->x + vel.x < _map->getParsedMap()[pos->y].size() && pos->y >= vel.y && checkMovable({
                translatePosCoordinates(pos->x + (vel.x / 2), _map->getMapWidth()),
                0.5f + (z * 0.01f),
                z,
            }, wallPass)) {
                pos->x += vel.x / 2;
                pos->y -= vel.y / 2;
                playerSprite->model->setPosition((RL::Vector3f){pos->x, pos->y, pos->z});
                playerSprite->model->setRotation(135.0f);
            }
        };

        void moveDownLeft(Pos *pos, Velocity vel, Sprite *playerSprite, bool wallPass)
        {
            float z = translatePosCoordinates(pos->y + (vel.y / 2), _map->getMapDepth());
            if (pos->x >= vel.x && pos->y + vel.y < _map->getParsedMap().size() && checkMovable({
                translatePosCoordinates(pos->x - (vel.x / 2), _map->getMapWidth()),
                0.5f + (z * 0.01f),
                z,
            }, wallPass)) {
                pos->x -= vel.x / 2;
                pos->y += vel.y / 2;
                playerSprite->model->setPosition((RL::Vector3f){pos->x, pos->y, pos->z});
                playerSprite->model->setRotation(315.0f);
            }
        };

        void moveDownRight(Pos *pos, Velocity vel, Sprite *playerSprite, bool wallPass)
        {
            float z = translatePosCoordinates(pos->y + (vel.y / 2), _map->getMapDepth());
            if (pos->x + vel.x < _map->getParsedMap()[pos->y].size() && pos->y + vel.y < _map->getParsedMap().size() && checkMovable({
                translatePosCoordinates(pos->x + (vel.x / 2), _map->getMapWidth()),
                0.5f + (z * 0.01f),
                z,
            }, wallPass)) {
                pos->x += vel.x / 2;
                pos->y += vel.y / 2;
                playerSprite->model->setPosition((RL::Vector3f){pos->x, pos->y, pos->z});
                playerSprite->model->setRotation(45.0f);
            }
        };

    private:
        std::shared_ptr<RL::Map> _map;
        std::shared_ptr<RL::InputManager> _inputManager;
        RL::CollisionManager _colManager;
        PlayerType type = Other;
};

#endif /* !MOVEMENTSYSTEM_HPP_ */
