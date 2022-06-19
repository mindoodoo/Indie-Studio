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
            Player_AI,
            Other
        };
        MovementSystem(std::shared_ptr<EntityManager> em, std::shared_ptr<RL::Map> map, std::shared_ptr<RL::InputManager> iM) : _map(map), _inputManager(iM)
        {
            _em = em;
        };
        ~MovementSystem() {};

        void update(float deltaTime, std::vector<EntityID> &playerIds, std::vector<EntityID> &aiBombLaying, std::vector<std::size_t> &deadPlayers, int &maxCoins) override {
            for (EntityID ent : EntityViewer<Pos, Velocity, Input, Sprite, CollisionObjectType>(*_em.get())) {
                _ent = ent;
                Pos* playerPos = _em->Get<Pos>(ent);
                Velocity* playerVel = _em->Get<Velocity>(ent);
                Input* playerMovement = _em->Get<Input>(ent);
                Sprite* playerSprite = _em->Get<Sprite>(ent);
                CollisionObjectType* playerType = _em->Get<CollisionObjectType>(ent);
                Skillset skills({0, 0, 0, false});
                bool wallPass = false;
                if (*playerType == PLAYER || *playerType == AI) {
                    if (ent == playerIds[0])
                        _type = Player_One;
                    else if (ent == playerIds[1])
                        _type = Player_Two;
                    else
                        _type = Player_AI;
                    skills = *_em->Get<Skillset>(ent);
                    wallPass = skills.wallPass;
                }
                float speedUp = skills.speedUp * 0.04;
                if (*playerType == AI && speedUp > (0.1 - playerVel->x))
                    speedUp = 0.1 - playerVel->x;
                else if (*playerType == AI)
                    speedUp /= 2;
                if (*playerType == PLAYER && speedUp > (0.15 - playerVel->x))
                    speedUp = 0.15 - playerVel->x;
                Velocity vel = *playerVel + speedUp;

                switch (playerMovement->pressedKey) {
                    case UP:
                    case UP2:
                        playerSprite->model->setCurrentAnim(1);
                        moveUp(playerPos, vel, playerSprite, wallPass);
                        break;
                    case DOWN:
                    case DOWN2:
                        playerSprite->model->setCurrentAnim(1);
                        moveDown(playerPos, vel, playerSprite, wallPass);
                        break;
                    case LEFT:
                    case LEFT2:
                        playerSprite->model->setCurrentAnim(1);
                        moveLeft(playerPos, vel, playerSprite,wallPass);
                        break;
                    case RIGHT:
                    case RIGHT2:
                        playerSprite->model->setCurrentAnim(1);
                        playerSprite->model->updateModelsAnimation();
                        moveRight(playerPos, vel, playerSprite, wallPass);
                        break;
                    case NONE:
                        if (playerSprite->model->getCurrentAnim() != 2)
                            playerSprite->model->setCurrentAnim(0);
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
            Sprite *player = _em->Get<Sprite>(_ent);
            Pos *playerPos = _em->Get<Pos>(_ent);
            for (EntityID ent : EntityViewer<Pos, Sprite, BombProperty, BombOwner>(*_em.get())) {
                Sprite *bomb = _em->Get<Sprite>(ent);
                Pos *bombPos = _em->Get<Pos>(ent); //remove again
                BombProperty *bombProperty = _em->Get<BombProperty>(ent);
                if (_colManager.collisionsWithModels((RL::Vector3f){pos.x, pos.y, pos.z}, *bomb->model)) {
                    for (Blocking blocking : bombProperty->blockingForPlayer) {
                        if (blocking.id == _ent && blocking.isBlocking)
                            return false;
                    }
                }
            }
            return true;
        }

        bool checkPressedUp() {
            if (_type == Player_One)
                return _inputManager->playerHasPressedKeyAsChar(UP);
            else if (_type == Player_Two)
                return _inputManager->playerHasPressedKeyAsChar(UP2);
            else
                return false;
        }

        bool checkPressedDown() {
            if (_type == Player_One)
                return _inputManager->playerHasPressedKeyAsChar(DOWN);
            else if (_type == Player_Two)
                return _inputManager->playerHasPressedKeyAsChar(DOWN2);
            else
                return false;
        }

        bool checkPressedLeft() {
            if (_type == Player_One)
                return _inputManager->playerHasPressedKeyAsChar(LEFT);
            else if (_type == Player_Two)
                return _inputManager->playerHasPressedKeyAsChar(LEFT2);
            else
                return false;
        }

        bool checkPressedRight() {
            if (_type == Player_One)
                return _inputManager->playerHasPressedKeyAsChar(RIGHT);
            else if (_type == Player_Two)
                return _inputManager->playerHasPressedKeyAsChar(RIGHT2);
            else
                return false;
        }

        void moveLeft(Pos *pos, Velocity vel, Sprite *playerSprite, bool wallPass)
        {
            if (checkPressedUp()) {
                moveUpLeft(pos, vel, playerSprite, wallPass);
                return;
            }
            if (checkPressedDown()) {
                moveDownLeft(pos, vel, playerSprite, wallPass);
                return;
            }
            float z = translatePosCoordinates(pos->y, _map->getMapDepth());
            if (pos->x >= vel.x && checkMovable({
                translatePosCoordinates(pos->x - vel.x, _map->getMapWidth()),
                0.5f,
                z,
            }, wallPass)) {
                pos->x -= vel.x;
                playerSprite->model->setPosition((RL::Vector3f){pos->x, pos->y, pos->z});
                playerSprite->model->setRotation(270.0f);
            }
        };

        void moveRight(Pos *pos, Velocity vel, Sprite *playerSprite, bool wallPass)
        {
            if (checkPressedUp()) {
                moveUpRight(pos, vel, playerSprite, wallPass);
                return;
            }
            if (checkPressedDown()) {
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
            if (checkPressedLeft()) {
                moveUpLeft(pos, vel, playerSprite, wallPass);
                return;
            }
            if (checkPressedRight()) {
                moveUpRight(pos, vel, playerSprite, wallPass);
                return;
            }
            float z = translatePosCoordinates(pos->y - vel.y, _map->getMapDepth());
            if (pos->y >= vel.y && checkMovable({
                translatePosCoordinates(pos->x, _map->getMapWidth()),
                0.5f,
                z,
            }, wallPass)) {
                pos->y -= vel.y;
                playerSprite->model->setPosition((RL::Vector3f){pos->x, pos->y, pos->z});
                playerSprite->model->setRotation(180.0f);
            }
        };

        void moveDown(Pos *pos, Velocity vel, Sprite *playerSprite, bool wallPass)
        {
            if (checkPressedLeft()) {
                moveDownLeft(pos, vel, playerSprite, wallPass);
                // playerSprite->model->setCurrentAnim(1);
                // playerSprite->model->updateModelsAnimation();
                return;
            }
            if (checkPressedRight()) {
                moveDownRight(pos, vel, playerSprite, wallPass);
                return;
            }
            float z = translatePosCoordinates(pos->y + vel.y, _map->getMapDepth());
            if (pos->y + vel.y < _map->getParsedMap().size() && checkMovable({
                translatePosCoordinates(pos->x, _map->getMapWidth()),
                0.5f,
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
                0.5f,
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
                0.5f,
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
                0.5f,
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
                0.5f,
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
        PlayerType _type = Other;
        EntityID _ent;
};

#endif /* !MOVEMENTSYSTEM_HPP_ */
