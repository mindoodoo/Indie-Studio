/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** CollisionSystem
*/

#ifndef COLLISIONSYSTEM_HPP_
#define COLLISIONSYSTEM_HPP_

#include <algorithm>

#include "ISystem.hpp"
#include "../GameEngine/Map.hpp"
#include "../GameEngine/CollisionManager.hpp"
#include "../Raylib/RaylibTypeEncaps.hpp"
#include "../SoundManager.hpp"
#include "../Window.hpp"

class CollisionSystem : public ISystem {
    public:
        CollisionSystem(std::shared_ptr<EntityManager> em, std::shared_ptr<RL::Window> window, std::shared_ptr<RL::SoundManager> sM, std::shared_ptr<RL::Map> map) : _window(window), _soundManager(sM), _map(map)
        {
            _em = em;
        };
        ~CollisionSystem() {};

        void update(float deltaTime, std::vector<EntityID> &playerIds, std::vector<EntityID> &aiBombLaying) override {
            _destroyQueue.clear();
            for (EntityID ent : EntityViewer<Pos, Sprite, CollisionObjectType>(*_em.get())) {
                for (EntityID other : EntityViewer<Pos, Sprite, CollisionObjectType>(*_em.get())) {
                    Pos *entPos = _em->Get<Pos>(ent);
                    Sprite *entModel = _em->Get<Sprite>(ent);
                    Sprite *otherModel = _em->Get<Sprite>(other);
                    RL::Vector3f pos(entPos->x, entPos->y, entPos->z);
                    CollisionObjectType* type1 = _em->Get<CollisionObjectType>(ent);
                    CollisionObjectType* type2 = _em->Get<CollisionObjectType>(other);
                    if (*type1 == ITEM)
                        pos = entModel->model->getPosition();
                    if (ent != other && _colManager.collisionsWithModels(*entModel->model, *otherModel->model)) {
                        _destroyQueue.push_back(checkCollisionType(ent, other));
                    }
                }
            }
            destroyEntities(_destroyQueue, playerIds);
        };

        void destroyEntities(std::vector<EntityID> _destroyQueue, std::vector<EntityID> &playerIds) {
            for (EntityID id : _destroyQueue) {
                if (id != INVALID_ENTITY) {
                    Sprite *entModel = _em->Get<Sprite>(id);
                    _em->DestroyEntity(id);
                    _window->removeDrawable(entModel->model);
                    if (checkIfVectorContains(playerIds, id)) {
                        _soundManager->playSpecificSoundFx("hurt");
                        std::replace(playerIds.begin(), playerIds.end(), id, INVALID_ENTITY);
                    }
                }
            }
        }

        bool checkIfVectorContains(std::vector<EntityID> vector, EntityID id) {
            if (std::find(vector.begin(), vector.end(), id) != vector.end())
                return true;
            return false;
        }

        EntityID checkCollisionType(EntityID ent, EntityID other) {
            CollisionObjectType* type1 = _em->Get<CollisionObjectType>(ent);
            CollisionObjectType* type2 = _em->Get<CollisionObjectType>(other);

            if (*type1 == *type2)
                return INVALID_ENTITY;
            if (*type1 < *type2)
                return callCollisionHandler(ent, type1, other, type2);
            else
                return callCollisionHandler(other, type2, ent, type1);
        };

        EntityID callCollisionHandler(EntityID lowEnt, CollisionObjectType* low, EntityID highEnt, CollisionObjectType* high) {
            switch (*low) {
                case ITEM:
                    return handleItemCollision(lowEnt, low, highEnt, high);
                case BREAKABLE_BLOCK:
                case PLAYER:
                case AI:
                case MONSTER:
                    return handleBombCollision(lowEnt, low, highEnt, high);
            }
            return INVALID_ENTITY;
        };

        EntityID handleItemCollision(EntityID itemEnt, CollisionObjectType* item, EntityID highEnt, CollisionObjectType* high) {
            if ((*high == PLAYER || *high == AI) && !checkIfVectorContains(_destroyQueue, itemEnt)) {
                Skillset* playerSkills = _em->Get<Skillset>(highEnt);
                Skillset* skillIncrease = _em->Get<Skillset>(itemEnt);
                Pos* itemPos = _em->Get<Pos>(itemEnt);
                *playerSkills += *skillIncrease;
                if (skillIncrease->bombUp) {
                    BombCapacity* playerBombCapacity = _em->Get<BombCapacity>(highEnt);
                    playerBombCapacity->curCapacity += skillIncrease->bombUp;
                    playerBombCapacity->totalAmount += skillIncrease->bombUp;
                    std::cout << "updated bomb capacity to " << playerBombCapacity->totalAmount << std::endl;
                }
                if (skillIncrease->fireUp)
                    std::cout << "updated fire up" << std::endl;
                if (skillIncrease->speedUp)
                    std::cout << "updated speed up" << std::endl;
                if (skillIncrease->wallPass)
                    std::cout << "updated wallPass" << std::endl;
                _soundManager->playSpecificSoundFx("Item1");
                _map->removeItem({(int)itemPos->x, (int)itemPos->y});
                return itemEnt;
            }
            return INVALID_ENTITY;
        };

        EntityID handleBombCollision(EntityID lowEnt, CollisionObjectType* low, EntityID highEnt, CollisionObjectType* high) {
            if (*high == EXPLOSION && *low == MONSTER && !checkIfVectorContains(_destroyQueue, lowEnt)) {
                BombOwner* player = _em->Get<BombOwner>(highEnt);
                Score* scoreIncrease = _em->Get<Score>(lowEnt);
                _em->Get<Score>(player->id)->score += scoreIncrease->score;
                std::cout << "bomb killed monster, score increase by " << scoreIncrease->score << std::endl;
                return lowEnt;
            } else if (*high == EXPLOSION && !checkIfVectorContains(_destroyQueue, lowEnt)) {
                std::cout << "bomb killed player or breakable block " << std::endl;
                return lowEnt;
            }
            return INVALID_ENTITY;
        };

    private:
        std::shared_ptr<RL::Window> _window;
        std::shared_ptr<RL::Map> _map;
        RL::CollisionManager _colManager;
        std::vector<EntityID> _destroyQueue;
        std::shared_ptr<RL::SoundManager> _soundManager;
};

#endif /* !COLLISIONSYSTEM_HPP_ */
