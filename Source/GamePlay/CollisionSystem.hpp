/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** CollisionSystem
*/

#ifndef COLLISIONSYSTEM_HPP_
#define COLLISIONSYSTEM_HPP_

#include "ISystem.hpp"
#include "../Map.hpp"

class CollisionSystem : public ISystem {
    public:
        CollisionSystem(std::shared_ptr<EntityManager> em, std::shared_ptr<RL::Map> map) : _map(map)
        {
            _em = em;
        };
        ~CollisionSystem() {};

        void update(float deltaTime) override {
            // handle collision by raylib?
            for (EntityID ent : EntityViewer<Pos, Sprite, CollisionObjectType>(*_em.get())) {
                for (EntityID other : EntityViewer<Pos, Sprite>(*_em.get())) {
                    if (ent != other) { // && they collide
                        checkCollisionType(ent, other);
                    }
                }
            }
        };

        void checkCollisionType(EntityID ent, EntityID other) {
            CollisionObjectType* type1 = _em->Get<CollisionObjectType>(ent);
            CollisionObjectType* type2 = _em->Get<CollisionObjectType>(other);

            if (*type1 == *type2)
                return;
            if (*type1 < *type2)
                callCollisionHandler(ent, type1, other, type2);
            else
                callCollisionHandler(other, type2, ent, type1);
        };

        void callCollisionHandler(EntityID lowEnt, CollisionObjectType* low, EntityID highEnt, CollisionObjectType* high) {
            switch (*low) {
                case ITEM:
                    handleItemCollision(lowEnt, low, highEnt, high);
                    break;
                case BREAKABLE_BLOCK:
                case PLAYER:
                case MONSTER:
                    handleBombCollision(lowEnt, low, highEnt, high);
                    break;
            }
        };

        void handleItemCollision(EntityID itemEnt, CollisionObjectType* item, EntityID highEnt, CollisionObjectType* high) {
            if (*high == PLAYER) {
                Skillset* playerSkills = _em->Get<Skillset>(highEnt);
                Skillset* skillIncrease = _em->Get<Skillset>(itemEnt);
                *playerSkills += *skillIncrease;
                _em->DestroyEntity(itemEnt);
            }
        };

        void handleBombCollision(EntityID lowEnt, CollisionObjectType* low, EntityID highEnt, CollisionObjectType* high) {
            if (*high == BOMB && *low == MONSTER) {
                BombOwner* player = _em->Get<BombOwner>(highEnt);
                Score* scoreIncrease = _em->Get<Score>(lowEnt);
                _em->Get<Score>(player->id)->score += scoreIncrease->score;
                _em->DestroyEntity(lowEnt);
            } else if (*high == BOMB) {
                _em->DestroyEntity(lowEnt);
            }
        };

    private:
        std::shared_ptr<RL::Map> _map;
};

#endif /* !COLLISIONSYSTEM_HPP_ */
