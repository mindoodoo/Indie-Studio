/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** AISystem
*/

#ifndef AISYSTEM_HPP_
#define AISYSTEM_HPP_

#include <math.h>

#include "ISystem.hpp"
#include "../GameEngine/Map.hpp"
#include "../GameEngine/CollisionManager.hpp"
#include "../Raylib/RaylibTypeEncaps.hpp"
#include "../AI/AStar.hpp"

class AISystem : public ISystem {
    public:
        enum TargetType {
            CRATE,
            ITEM,
            PLAYER,
            BOMB,
            RANDOM
        };
        AISystem(std::shared_ptr<EntityManager> em, std::shared_ptr<RL::Map> map) : _map(map) {
            _em = em;
            _target = {0, 0, 0};
            _scanRadius = 5;
            _bombScanRadius = 5;
            _detectedBomb = false;
            _targetType = RANDOM;
        };
        ~AISystem() {};

        void update(float deltaTime, std::vector<EntityID> &playerIds, std::vector<EntityID> &aiBombLaying) {
            for (EntityID ent : EntityViewer<Pos, Sprite, CollisionObjectType>(*_em.get())) {
                _foundTarget = false;
                _bombPos.clear();
                CollisionObjectType* type = _em->Get<CollisionObjectType>(ent);
                if (*type == AI) {
                    Pos* pos = _em->Get<Pos>(ent);
                    Skillset* skills = _em->Get<Skillset>(ent);
                    _bombScanRadius = 5 + skills->fireUp;
                    Input* input = _em->Get<Input>(ent);
                    bool saveDetectedBomb = _detectedBomb;
                    _detectedBomb = false;
                    scanForBombs(pos);
                    if (_detectedBomb && !saveDetectedBomb)
                        escapeBombRadius(pos);
                    if (_path.empty()) {
                        if (_targetType != ITEM && _target.x != 0 && _target.y != 0 && _target.z != 0 && 
                            (_detectedBomb == saveDetectedBomb || (!_detectedBomb && saveDetectedBomb))) {
                            // lay bomb at target position
                            if (canEscapeBomb(pos)) {
                                aiBombLaying.push_back(ent);
                                return;
                            }
                        }
                        scanForNewTarget(pos, ent, playerIds);
                    }
                    if (_path.empty()) {
                        input->pressedKey = NONE;
                        return;
                    }
                    findTarget(ent, pos, input, playerIds);
                }
            }
        };

        void findTarget(EntityID ent, Pos *pos, Input *input, std::vector<EntityID> playerIds) {
            coordinates_t nextWalkingPoint = _path.front();
            Pos roundedPos = Pos({round_up(pos->x, 1), round_up(pos->y, 1)});
            if (roundedPos.x == nextWalkingPoint.second && roundedPos.y == nextWalkingPoint.first) {
                if (_path.empty()) {
                    input->pressedKey = NONE;
                    return;
                }
                _path.pop_front();
                nextWalkingPoint = _path.front();
            }

            Pos walkingDirection = Pos({roundedPos.x - nextWalkingPoint.second, roundedPos.y - nextWalkingPoint.first, 0});

            if (abs(walkingDirection.x) > abs(walkingDirection.y)) {
                if (walkingDirection.x > 0)
                    input->pressedKey = LEFT;
                else if (walkingDirection.x < 0)
                    input->pressedKey = RIGHT;
            } else {
                if (walkingDirection.y > 0)
                    input->pressedKey = UP;
                else if (walkingDirection.y < 0)
                    input->pressedKey = DOWN;
            }
            if (walkingDirection.x == 0 && walkingDirection.y == 0)
                input->pressedKey = NONE;
        }

        float round_up(float number, int decimal_places) {
            float multiplier = std::pow(10.0, decimal_places);
            return std::ceil(number * multiplier) / multiplier;
        }

        coordinates_t roundPos(float x, float y) {
            int roundX = round(x);
            int roundY = round(y);
            if (_map->getParsedMap()[roundY][roundX].tile != 1 &&
                _map->getParsedMap()[roundY][roundX].tile != 2)
                return {roundX, roundY};
            int ceilX = std::ceil(x);
            int ceilY = std::ceil(y);
            int floorX = std::floor(x);
            int floorY = std::floor(y);
            if (_map->getParsedMap()[ceilY][ceilX].tile != 1 &&
                _map->getParsedMap()[ceilY][ceilX].tile != 2)
                return {ceilX, ceilY};
            if (_map->getParsedMap()[floorY][floorX].tile != 1 &&
                _map->getParsedMap()[floorY][floorX].tile != 2)
                return {floorX, floorY};
            if (_map->getParsedMap()[ceilY][floorX].tile != 1 &&
                _map->getParsedMap()[ceilY][floorX].tile != 2)
                return {floorX, ceilY};
            if (_map->getParsedMap()[floorY][ceilX].tile != 1 &&
                _map->getParsedMap()[floorY][ceilX].tile != 2)
                return {ceilX, floorY};
        }

        void scanForNewTarget(Pos *pos, EntityID ent, std::vector<EntityID> playerIds) {
            scanForPlayers(pos, ent, playerIds);
            if (!_foundTarget)
                scanForItem(pos);
            if (!_foundTarget)
                scanForBreakableBlock(pos);
            if (!_foundTarget && !_detectedBomb)
                setRandomTarget(pos);
        }

        bool isOutOfBombReach(Pos pos) {
            int neededDistance = _bombScanRadius - 2;
            for (Pos bomb : _bombPos) {
                if (((pos.x != bomb.x && pos.y != bomb.y)
                    || abs(pos.x - bomb.x) > neededDistance || abs(pos.y - bomb.y) > neededDistance))
                    continue;
                else
                    return false;
            }
            return true;
        }

        void checkForPath(Pos *pos) {
            coordinates_t AIPos = roundPos(pos->x, pos->y);
            coordinates_t targetPosition = {_target.x, _target.y};

            if (AIPos == targetPosition)
                return;
            _path = calculateAStar(AIPos, targetPosition, _map->getParsedMap());

            for (int i = 0; i < _path.size(); i++) {
                // check that all paths are out of bomb radius
                if (!isOutOfBombReach({(float)_path[i].second, (float)_path[i].first, 1})) {
                    _path.clear();
                    _foundTarget = false;
                    return;
                }
            }
            if (_path.empty()) {
                _foundTarget = false;
            } else
                _foundTarget = true;
        }

        void escapeBombRadius(Pos *pos) {
            coordinates_t AIPos = roundPos(pos->x, pos->y);
            coordinates_t bombPosition = {_target.x, _target.y};

            _path = avoidBomb(AIPos, bombPosition, _bombScanRadius - 2, _map->getParsedMap());

            if (_path.empty()) {
                _foundTarget = false;
            } else
                _foundTarget = true;
        }

        bool canEscapeBomb(Pos *pos) {
            coordinates_t AIPos = roundPos(pos->x, pos->y);
            coordinates_t bombPosition = roundPos(pos->x, pos->y);
            std::deque<coordinates_t> path = avoidBomb(AIPos, bombPosition, _bombScanRadius - 2, _map->getParsedMap());

            for (int i = 0; i < path.size(); i++) {
                if (!isOutOfBombReach({(float)path[i].second, (float)path[i].first, 1}))
                    return false;
            }
            if (path.empty()) {
                _foundTarget = false;
                return false;
            } else {
                _path = path;
                _target = {(float)bombPosition.second, (float)bombPosition.first, 1};
                return true;
            }
        }

        void scanForBombs(Pos* pos) {
            std::vector<Pos> bombPos;
            for (EntityID ent : EntityViewer<Pos, CollisionObjectType>(*_em.get())) {
                CollisionObjectType type = *_em->Get<CollisionObjectType>(ent);
                if (type == CollisionObjectType::BOMB || type == EXPLOSION)
                    bombPos.push_back(*_em->Get<Pos>(ent));
            }

            for (int radius = 0; radius < _bombScanRadius; radius++) {
                int startX = (pos->x - radius) <= 0 ? 1 : (pos->x - radius);
                int startY = (pos->y - radius) <= 0 ? 1 : (pos->y - radius);
                int endX = (pos->x + radius) >= _map->getMapWidth() ? (_map->getMapWidth() - 1) : (pos->x + radius);
                int endY = (pos->y + radius) >= _map->getMapDepth() ? (_map->getMapDepth() - 1) : (pos->y + radius);
                for (int y = startY; y <= endY; y++) {
                    for (int x = startX; x <= endX; x++) {
                        for (Pos curPos : bombPos) {
                            if (!_detectedBomb && round(curPos.x) == x && round(curPos.y) == y) {
                                // std::cout << "found BOMB" << std::endl;
                                _target = {(float)x, (float)y, 1};
                                _bombPos.push_back(_target);
                                _detectedBomb = true;
                                _targetType = BOMB;
                            } else if (round(curPos.x) == x && round(curPos.y) == y) {
                                _bombPos.push_back({(float)x, (float)y, 1});
                            }
                        }
                        
                    }
                }
            }
        };

        void scanForPlayers(Pos* pos, EntityID ent, std::vector<EntityID> playerIds) {
            std::vector<Pos> playerPos;
            for (EntityID id : playerIds) {
                if (id != INVALID_ENTITY && ent != id)
                    playerPos.push_back(*_em->Get<Pos>(id));
            }

            for (int radius = 0; radius < _scanRadius; radius++) {
                int startX = (pos->x - radius) <= 0 ? 1 : (pos->x - radius);
                int startY = (pos->y - radius) <= 0 ? 1 : (pos->y - radius);
                int endX = (pos->x + radius) >= _map->getMapWidth() ? (_map->getMapWidth() - 1) : (pos->x + radius);
                int endY = (pos->y + radius) >= _map->getMapDepth() ? (_map->getMapDepth() - 1) : (pos->y + radius);
                for (int y = startY; y <= endY; y++) {
                    for (int x = startX; x <= endX; x++) {
                        for (Pos curPos : playerPos) {
                            if (round(curPos.x) == x && round(curPos.y) == y) {
                                _target = {(float)x, (float)y, 1};
                                checkForPath(pos);
                                if (!_foundTarget)
                                    continue;
                                _targetType = PLAYER;
                                std::cout << "found PLAYER" << std::endl;
                                return;
                            }
                        }
                    }
                }
            }
        };

        void scanForItem(Pos* pos) {
            for (int radius = 0; radius < _scanRadius; radius++) {
                int startX = (pos->x - radius) <= 0 ? 1 : (pos->x - radius);
                int startY = (pos->y - radius) <= 0 ? 1 : (pos->y - radius);
                int endX = (pos->x + radius) >= _map->getMapWidth() ? (_map->getMapWidth() - 1) : (pos->x + radius);
                int endY = (pos->y + radius) >= _map->getMapDepth() ? (_map->getMapDepth() - 1) : (pos->y + radius);
                for (int y = startY; y <= endY; y++) {
                    for (int x = startX; x <= endX; x++) {
                        if (_map->getParsedMap()[y][x].tile == SPEED_UP ||
                            _map->getParsedMap()[y][x].tile == BOMB_UP ||
                            _map->getParsedMap()[y][x].tile == FIRE_UP ||
                            _map->getParsedMap()[y][x].tile == WALLPASS) {
                            _target = {(float)x, (float)y, 1};
                            checkForPath(pos);
                            if (!_foundTarget)
                                continue;
                            _targetType = ITEM;
                            std::cout << "found ITEM" << std::endl;
                            return;
                        }
                    }
                }
            }
        };

        void scanForBreakableBlock(Pos* pos) {
            for (int radius = 0; radius < _scanRadius; radius++) {
                int startX = (pos->x - radius) <= 0 ? 1 : (pos->x - radius);
                int startY = (pos->y - radius) <= 0 ? 1 : (pos->y - radius);
                int endX = (pos->x + radius) >= _map->getMapWidth() ? (_map->getMapWidth() - 1) : (pos->x + radius);
                int endY = (pos->y + radius) >= _map->getMapDepth() ? (_map->getMapDepth() - 1) : (pos->y + radius);
                for (int y = startY; y <= endY; y++) {
                    for (int x = startX; x <= endX; x++) {
                        if (_map->getParsedMap()[y][x].tile == BREAKABLE_OBJECT) {
                            _target = {(float)x, (float)y, 1};
                            checkForPath(pos);
                            if (!_foundTarget)
                                continue;
                            _targetType = CRATE;
                            std::cout << "found CRATE" << std::endl;
                            return;
                        }
                    }
                }
            }
        };

        void setRandomTarget(Pos *pos) {
            int iterations = 0;
            while (!_foundTarget && iterations < 10) {
                int randX = rand() % (_map->getMapWidth() - 1);
                int randY = rand() % (_map->getMapDepth() - 1);
                std::cout << "RANDOM VALS: " << randX << ", " << randY << std::endl;
                float x = randX + 1;
                float y = randY + 1;
                _target = {x, y, 1};
                checkForPath(pos);
                iterations++;
            }
            if (!_foundTarget) {
                _path.clear();
            }
            _targetType = RANDOM;
        }

    private:
        std::shared_ptr<RL::Map> _map;
        RL::CollisionManager _colManager;
        bool _detectedBomb;
        bool _foundTarget;
        Pos _target;
        int _scanRadius;
        int _bombScanRadius;
        TargetType _targetType;

        //AStar implementation test
        std::deque<coordinates_t> _path;
        std::vector<Pos> _bombPos;
};

#endif /* !AISYSTEM_HPP_ */
