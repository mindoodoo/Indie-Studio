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
        struct Target {
            Pos pos;
            TargetType type;
            std::deque<coordinates_t> path;
        };
        AISystem(std::shared_ptr<EntityManager> em, std::shared_ptr<RL::Map> map) : _map(map) {
            _em = em;
            _target = {0, 0, 0};
            _path = {};
            _scanRadius = 5;
            _bombScanRadius = 5;
            _detectedBomb = false;
            _targetType = RANDOM;
            _blockingTiles.push_back(1);
            _blockingTiles.push_back(2);
        };
        ~AISystem() {};

        void update(float deltaTime, std::vector<EntityID> &playerIds, std::vector<EntityID> &aiBombLaying, std::vector<std::size_t> &deadPlayers, int &maxCoins) {
            for (EntityID ent : EntityViewer<Pos, Sprite, CollisionObjectType, AIData>(*_em.get())) {
                _ent = ent;
                _foundTarget = false;
                _bombPos.clear();
                _bombMap.clear();
                _possibleTargets.clear();
                Pos* pos = _em->Get<Pos>(ent);
                Skillset* skills = _em->Get<Skillset>(ent);
                Input* input = _em->Get<Input>(ent);
                AIData* data = _em->Get<AIData>(ent);
                initValues(data, *skills);
                if (_blockingTiles.size() == 2 && skills->wallPass)
                    _blockingTiles.pop_back();
                bool saveDetectedBomb = _detectedBomb;
                _detectedBomb = false;
                scanForBombs(pos);
                initBombMap();
                if (_detectedBomb && !saveDetectedBomb)
                    escapeBombRadius(pos);
                if (_path.empty()) {
                    if (_targetType != ITEM_TARGET && _target.x != 0 && _target.y != 0 && _target.z != 0 && 
                        (_detectedBomb == saveDetectedBomb || (!_detectedBomb && saveDetectedBomb))
                        && hasBombEffect(pos)) {
                        // lay bomb at target position
                        if (canEscapeBomb(pos)) {
                            aiBombLaying.push_back(ent);
                            updateAIData(data);
                            return;
                        }
                    }
                    scanForNewTarget(pos, ent, playerIds);
                }
                if (_path.empty()) {
                    input->pressedKey = NONE;
                    updateAIData(data);
                    return;
                }
                findTarget(ent, pos, input, playerIds);
                updateAIData(data);
            }
        };

        bool isInMap(int x, int y) {
            if (x <= 0 || y <= 0) 
                return false;
            if (x + 1 >= _map->getMapWidth() || y + 1 >= _map->getMapDepth())
                return false;
            return true;
        }

        void initBombMap() {
            for (std::vector<gfx_tile_t> line : _map->getParsedMap())
                _bombMap.push_back(line);
            for (EntityID ent : EntityViewer<Pos, BombOwner, BombProperty, CollisionObjectType>(*_em.get())) {
                CollisionObjectType type = *_em->Get<CollisionObjectType>(ent);
                BombProperty blockable = *_em->Get<BombProperty>(ent);
                BombOwner bombOwner = *_em->Get<BombOwner>(ent);
                if (type == BOMB) {
                    for (Blocking blocking : blockable.blockingForPlayer) {
                        if (blocking.id == _ent && blocking.isBlocking) {
                            Pos pos = *_em->Get<Pos>(ent);
                            _bombMap[pos.y][pos.x].tile = 1;
                            if (isInMap(pos.x + 1, pos.y))
                                _bombMap[pos.y][pos.x + 1].tile = 1;
                            if (isInMap(pos.x - 1, pos.y))
                                _bombMap[pos.y][pos.x - 1].tile = 1;
                            if (isInMap(pos.x, pos.y + 1))
                                _bombMap[pos.y + 1][pos.x].tile = 1;
                            if (isInMap(pos.x, pos.y - 1))
                                _bombMap[pos.y - 1][pos.x].tile = 1;
                        }
                    }
                }
            }
        }

        void initValues(AIData *data, Skillset skills) {
            _target = data->target;
            _path = data->path;
            _scanRadius = data->scanRadius;
            _bombScanRadius = 5 + skills.fireUp;
            _detectedBomb = data->detectedBomb;
            _targetType = data->targetType;
            _blockingTiles = data->blockingTiles;
        };

        void updateAIData(AIData *data) {
            data->target = _target;
            data->path = _path;
            data->scanRadius = _scanRadius;
            data->detectedBomb = _detectedBomb;
            data->targetType = _targetType;
            data->blockingTiles = _blockingTiles;
        }

        bool hasBombEffect(Pos *pos) {
            std::vector<Pos> opponents;
            std::vector<Pos> surroundingPos;
            for (EntityID ent : EntityViewer<Pos, BombCapacity>(*_em.get())) {
                opponents.push_back(*_em->Get<Pos>(ent));
            }
            surroundingPos.push_back({pos->x - 1, pos->y});
            surroundingPos.push_back({pos->x + 1, pos->y});
            surroundingPos.push_back({pos->x, pos->y - 1});
            surroundingPos.push_back({pos->x, pos->y + 1});

            for (Pos curPos : surroundingPos) {
                for (Pos opponent : opponents) {
                    if (round_up(opponent.x, 1) == round_up(curPos.x, 1) && round_up(opponent.y, 1) == round_up(curPos.y, 1))
                        return true;
                }
                if (_map->getParsedMap()[round(curPos.y)][round(curPos.x)].tile == 2)
                    return true;
            }
            return false;
        }

        void findTarget(EntityID ent, Pos *pos, Input *input, std::vector<EntityID> playerIds) {
            coordinates_t nextWalkingPoint = _path.front();
            Pos roundedPos = Pos({round_up(pos->x, 1), round_up(pos->y, 1)});
            if (roundedPos.x == nextWalkingPoint.second && roundedPos.y == nextWalkingPoint.first) {
                if (_path.empty()) {
                    input->pressedKey = NONE;
                    return;
                }
                _path.pop_front();
                if (_path.empty()) {
                    input->pressedKey = NONE;
                    return;
                }
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
            return {roundX, roundY};
        }

        void scanForNewTarget(Pos *pos, EntityID ent, std::vector<EntityID> playerIds) {
            scanForObjects(pos, ent, playerIds);
            if (_possibleTargets.empty() && !_detectedBomb)
                setRandomTarget(pos);
            if (!_possibleTargets.empty()) {
                // delete a few crates to make player + items more relevant
                int chosenIndex = rand() % _possibleTargets.size();
                _target = _possibleTargets[chosenIndex].pos;
                _targetType = _possibleTargets[chosenIndex].type;
                _path = _possibleTargets[chosenIndex].path;
            }
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
            _path = calculateAStar(AIPos, targetPosition, _bombMap, _blockingTiles);

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

            _path = avoidBomb(AIPos, bombPosition, _bombScanRadius - 2, _bombMap, _blockingTiles);

            if (_path.empty()) {
                _foundTarget = false;
            } else
                _foundTarget = true;
        }

        bool canEscapeBomb(Pos *pos) {
            coordinates_t AIPos = roundPos(pos->x, pos->y);
            coordinates_t bombPosition = roundPos(pos->x, pos->y);
            std::deque<coordinates_t> path = avoidBomb(AIPos, bombPosition, _bombScanRadius - 2, _bombMap, _blockingTiles);

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
                                _target = {(float)x, (float)y, 1};
                                _bombPos.push_back(_target);
                                _detectedBomb = true;
                                _targetType = BOMB_TARGET;
                            } else if (round(curPos.x) == x && round(curPos.y) == y) {
                                _bombPos.push_back({(float)x, (float)y, 1});
                            }
                        }
                        
                    }
                }
            }
        };

        void scanForObjects(Pos* pos, EntityID ent, std::vector<EntityID> playerIds) {
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
                        scanForPlayers(pos, x, y, playerPos);
                        scanForItem(pos, x, y);
                        scanForBreakableBlock(pos, x, y);
                    }
                }
            }
        };

        void scanForPlayers(Pos* pos, int x, int y, std::vector<Pos> playerPos) {
            for (Pos curPos : playerPos) {
                if (round(curPos.x) == x && round(curPos.y) == y) {
                    _target = {(float)x, (float)y, 1};
                    checkForPath(pos);
                    if (!_foundTarget)
                        continue;
                    _possibleTargets.push_back({_target, PLAYER_TARGET, _path});
                }
            }
        }

        void scanForItem(Pos* pos, int x, int y) {
            if (_map->getParsedMap()[y][x].tile == SPEED_UP ||
                _map->getParsedMap()[y][x].tile == BOMB_UP ||
                _map->getParsedMap()[y][x].tile == FIRE_UP ||
                _map->getParsedMap()[y][x].tile == WALLPASS) {
                _target = {(float)x, (float)y, 1};
                checkForPath(pos);
                if (!_foundTarget)
                    return;
                _possibleTargets.push_back({_target, ITEM_TARGET, _path});
            }
        };

        void scanForBreakableBlock(Pos* pos, int x, int y) {
            
            if (_map->getParsedMap()[y][x].tile == BREAKABLE_OBJECT) {
                _target = {(float)x, (float)y, 1};
                checkForPath(pos);
                if (!_foundTarget)
                    return;
                _possibleTargets.push_back({_target, CRATE_TARGET, _path});
            }
        };

        void setRandomTarget(Pos *pos) {
            int iterations = 0;
            while (!_foundTarget && iterations < 10) {
                int randX = rand() % (_map->getMapWidth() - 1);
                int randY = rand() % (_map->getMapDepth() - 1);
                float x = randX + 1;
                float y = randY + 1;
                _target = {x, y, 1};
                checkForPath(pos);
                iterations++;
            }
            if (!_foundTarget) {
                _path.clear();
            }
            _possibleTargets.push_back({_target, RANDOM, _path});
        }

    private:
        std::shared_ptr<RL::Map> _map;
        std::vector<std::vector<gfx_tile_t>> _bombMap;
        RL::CollisionManager _colManager;
        bool _detectedBomb; // as AI component
        bool _foundTarget;
        Pos _target; // as AI component
        TargetType _targetType; // as AI component
        int _scanRadius; // as AI component
        int _bombScanRadius;
        std::vector<Target> _possibleTargets;
        EntityID _ent;

        //AStar implementation test
        std::deque<coordinates_t> _path; // as AI component
        std::vector<Pos> _bombPos;
        std::vector<int> _blockingTiles; // as AI component
};

#endif /* !AISYSTEM_HPP_ */
