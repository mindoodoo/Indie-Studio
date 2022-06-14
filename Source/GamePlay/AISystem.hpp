/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** AISystem
*/

#ifndef AISYSTEM_HPP_
#define AISYSTEM_HPP_

#include "ISystem.hpp"
#include "../GameEngine/Map.hpp"
#include "../GameEngine/CollisionManager.hpp"
#include "../Raylib/RaylibTypeEncaps.hpp"

class AISystem : public ISystem {
    public:
        AISystem(std::shared_ptr<EntityManager> em, std::shared_ptr<RL::Map> map) : _map(map) {
            _em = em;
        };
        ~AISystem() {};

        void update(float deltaTime, std::vector<EntityID> &playerIds, std::vector<EntityID> &aiBombLaying) {
            for (EntityID ent : EntityViewer<Pos, Sprite, CollisionObjectType>(*_em.get())) {
                CollisionObjectType* type = _em->Get<CollisionObjectType>(ent);
                if (*type == AI) {
                    Input* input = _em->Get<Input>(ent);
                    switch (rand() % 6) {
                        case 0:
                            input->pressedKey = UP;
                            break;
                        case 1:
                            input->pressedKey = DOWN;
                            break;
                        case 2:
                            input->pressedKey = LEFT;
                            break;
                        case 3:
                            input->pressedKey = RIGHT;
                            break;
                        case 4:
                            input->pressedKey = NONE;
                            aiBombLaying.push_back(ent);
                            break;
                        default:
                            input->pressedKey = NONE;
                    }
                    // scan area of radius (maybe 5)
                    // check for player and other ais to kill it
                    // check for items
                    // otherwise lay bomb and avoid explosion
                    // after setting a target, move there with pathfinding algorithm (movement over Input component)
                }
            }
        };

    private:
        std::shared_ptr<RL::Map> _map;
        RL::CollisionManager _colManager;
};

#endif /* !AISYSTEM_HPP_ */
