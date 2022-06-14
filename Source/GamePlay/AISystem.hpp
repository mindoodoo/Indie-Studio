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

class AISystem : public ISystem {
    public:
        AISystem(std::shared_ptr<EntityManager> em, std::shared_ptr<RL::Map> map) : _map(map) {
            _em = em;
            _target = {0, 0, 0};
            _scanRadius = 5;
        };
        ~AISystem() {};

        void update(float deltaTime, std::vector<EntityID> &playerIds, std::vector<EntityID> &aiBombLaying) {
            for (EntityID ent : EntityViewer<Pos, Sprite, CollisionObjectType>(*_em.get())) {
                _foundTarget = false;
                Pos* pos = _em->Get<Pos>(ent);
                CollisionObjectType* type = _em->Get<CollisionObjectType>(ent);
                if (*type == AI) {
                    // TODO: avoid bomb as first priority
                    scanForPlayers(pos, ent, playerIds);
                    if (!_foundTarget)
                        scanForItem(pos);
                    if (!_foundTarget)
                        scanForBreakableBlock(pos);
                    if (!_foundTarget)
                        setRandomTarget();
                    Input* input = _em->Get<Input>(ent);
                    // after setting a target, move there with pathfinding algorithm (movement over Input component)
                    
                    // random (stupid) actions
                    // switch (rand() % 6) {
                    //     case 0:
                    //         input->pressedKey = UP;
                    //         break;
                    //     case 1:
                    //         input->pressedKey = DOWN;
                    //         break;
                    //     case 2:
                    //         input->pressedKey = LEFT;
                    //         break;
                    //     case 3:
                    //         input->pressedKey = RIGHT;
                    //         break;
                    //     case 4:
                    //         input->pressedKey = NONE;
                    //         aiBombLaying.push_back(ent);
                    //         break;
                    //     default:
                    //         input->pressedKey = NONE;
                    // }
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
                                std::cout << "found PLAYER" << std::endl;
                                _target = {(float)x, (float)y, 1};
                                _foundTarget = true;
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
                            std::cout << "found ITEM" << std::endl;
                            _target = {(float)x, (float)y, 1};
                            _foundTarget = true;
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
                            std::cout << "found CRATE" << std::endl;
                            _target = {(float)x, (float)y, 1};
                            _foundTarget = true;
                            return;
                        }
                    }
                }
            }
        };

        void setRandomTarget() {
            float x = (rand() % (_map->getMapWidth() - 1)) + 1;
            float y = (rand() % (_map->getMapDepth() - 1)) + 1;
            _target = {x, y, 1};
        }

    private:
        std::shared_ptr<RL::Map> _map;
        RL::CollisionManager _colManager;
        bool _foundTarget;
        Pos _target;
        int _scanRadius;
};

#endif /* !AISYSTEM_HPP_ */
