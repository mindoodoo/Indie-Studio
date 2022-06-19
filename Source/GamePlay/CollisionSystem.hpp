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
#include "../Raylib/UIManager.hpp"
#include "../SoundManager.hpp"
#include "../Window.hpp"

class CollisionSystem : public ISystem {
    public:
        CollisionSystem(std::shared_ptr<EntityManager> em, std::shared_ptr<RL::Window> window, std::shared_ptr<RL::SoundManager> sM, std::shared_ptr<RL::Map> map, bool coinMode)
         : _window(window), _soundManager(sM), _map(map), _uiManager(window)
        {
            _em = em;
            _coinMode = coinMode;
        };
        ~CollisionSystem() {};

        void update(float deltaTime, std::vector<EntityID> &playerIds, std::vector<EntityID> &aiBombLaying, std::vector<std::size_t> &deadPlayers, int &maxCoins) override {
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
                    if (ent != other) {
                        _destroyQueue.push_back(checkCollisionType(ent, other, _colManager.collisionsWithModels(*entModel->model, *otherModel->model), maxCoins));
                    }
                }
            }
            destroyEntities(_destroyQueue, playerIds, deadPlayers);
        };

        void destroyEntities(std::vector<EntityID> _destroyQueue, std::vector<EntityID> &playerIds, std::vector<std::size_t> &deadPlayers) {
            for (EntityID id : _destroyQueue) {
                if (id != INVALID_ENTITY) {
                    Sprite *entModel = _em->Get<Sprite>(id);
                    _em->DestroyEntity(id);
                    _window->removeDrawable(entModel->model);
                    if (checkIfVectorContains(playerIds, id)) {
                        _soundManager->playSpecificSoundFx("hitSound");
                        deadPlayers.push_back(getPlayerDead(playerIds, id));
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

        EntityID checkCollisionType(EntityID ent, EntityID other, bool collide, int &maxCoins) {
            CollisionObjectType* type1 = _em->Get<CollisionObjectType>(ent);
            CollisionObjectType* type2 = _em->Get<CollisionObjectType>(other);

            if (*type1 == *type2)
                return INVALID_ENTITY;
            if (*type1 < *type2)
                return callCollisionHandler(ent, type1, other, type2, collide, maxCoins);
            else
                return callCollisionHandler(other, type2, ent, type1, collide, maxCoins);
        };

        EntityID callCollisionHandler(EntityID lowEnt, CollisionObjectType* low, EntityID highEnt, CollisionObjectType* high, bool collide, int &maxCoins) {
            switch (*low) {
                case ITEM:
                    return handleItemCollision(lowEnt, low, highEnt, high, collide, maxCoins);
                case BREAKABLE_BLOCK:
                case PLAYER:
                case AI:
                case MONSTER:
                    return handleBombCollision(lowEnt, low, highEnt, high, collide);
            }
            return INVALID_ENTITY;
        };

        EntityID handleCoinCollision(EntityID itemEnt, CollisionObjectType* item, EntityID highEnt, CollisionObjectType* high, int &maxCoins) {
            if ((*high == PLAYER || *high == AI) && !checkIfVectorContains(_destroyQueue, itemEnt)) {
                Sprite* itemSprite = _em->Get<Sprite>(itemEnt);
                if (itemSprite->model->isHidden())
                    return INVALID_ENTITY;
                Score* playerScore = _em->Get<Score>(highEnt);
                UIPos* playerBasePos = _em->Get<UIPos>(highEnt);
                UiContinue* playerContinue = _em->Get<UiContinue>(highEnt);
                Score* scoreIncrease = _em->Get<Score>(itemEnt);
                Pos* itemPos = _em->Get<Pos>(itemEnt);
                playerScore->score += scoreIncrease->score;
                _uiManager.createCoin(*playerBasePos, playerScore->score, playerContinue->continueToRight);
                _soundManager->playSpecificSoundFx("Item1");
                maxCoins--;
                _map->removeItem({(int)itemPos->x, (int)itemPos->y});
                return itemEnt;
            }
            return INVALID_ENTITY;
        };

        EntityID handleItemCollision(EntityID itemEnt, CollisionObjectType* item, EntityID highEnt, CollisionObjectType* high, bool collide, int maxCoins) {
            if (!collide)
                return INVALID_ENTITY;
            if (_coinMode)
                return handleCoinCollision(itemEnt, item, highEnt, high, maxCoins);
            if ((*high == PLAYER || *high == AI) && !checkIfVectorContains(_destroyQueue, itemEnt)) {
                Sprite* itemSprite = _em->Get<Sprite>(itemEnt);
                if (itemSprite->model->isHidden())
                    return INVALID_ENTITY;
                Skillset* playerSkills = _em->Get<Skillset>(highEnt);
                UIPos* playerBasePos = _em->Get<UIPos>(highEnt);
                UiContinue* playerContinue = _em->Get<UiContinue>(highEnt);
                Skillset* skillIncrease = _em->Get<Skillset>(itemEnt);
                Pos* itemPos = _em->Get<Pos>(itemEnt);
                *playerSkills += *skillIncrease;
                if (skillIncrease->bombUp) {
                    BombCapacity* playerBombCapacity = _em->Get<BombCapacity>(highEnt);
                    playerBombCapacity->curCapacity += skillIncrease->bombUp;
                    playerBombCapacity->totalAmount += skillIncrease->bombUp;
                    _uiManager.createBombUp(*playerBasePos, playerSkills->bombUp, playerContinue->continueToRight);
                }
                if (skillIncrease->fireUp) {
                    _uiManager.createFireUp(*playerBasePos, playerSkills->fireUp, playerContinue->continueToRight);
                }
                if (skillIncrease->speedUp) {
                    _uiManager.createSpeedUp(*playerBasePos, playerSkills->speedUp, playerContinue->continueToRight);
                }
                if (skillIncrease->wallPass) {
                    _uiManager.createWallPass(*playerBasePos);
                }
                _soundManager->playSpecificSoundFx("Item1");
                _map->removeItem({(int)itemPos->x, (int)itemPos->y});
                return itemEnt;
            }
            return INVALID_ENTITY;
        };

        EntityID handleBombCollision(EntityID lowEnt, CollisionObjectType* low, EntityID highEnt, CollisionObjectType* high, bool collide) {
            if (*high == BOMB && (*low == PLAYER || *low == AI)) {
                BombProperty* bombProperty = _em->Get<BombProperty>(highEnt);
                BombOwner* bombOwner = _em->Get<BombOwner>(highEnt);
                Sprite* bomb = _em->Get<Sprite>(highEnt);
                Pos* bombPos = _em->Get<Pos>(highEnt);
                Sprite* player = _em->Get<Sprite>(lowEnt);
                Pos* playerPos = _em->Get<Pos>(lowEnt);
                for (int i = 0; i < bombProperty->blockingForPlayer.size(); i++) {
                    if (bombProperty->blockingForPlayer[i].id == lowEnt) {
                        if (!bombProperty->blockingForPlayer[i].isBlocking && !collide)
                            bombProperty->blockingForPlayer[i].isBlocking = true;
                    }
                }
            }
            if (!collide)
                return INVALID_ENTITY;
            if (*high == EXPLOSION && *low == MONSTER && !checkIfVectorContains(_destroyQueue, lowEnt)) {
                BombOwner* player = _em->Get<BombOwner>(highEnt);
                Score* scoreIncrease = _em->Get<Score>(lowEnt);
                _em->Get<Score>(player->id)->score += scoreIncrease->score;
                return lowEnt;
            } else if (*high == EXPLOSION && !checkIfVectorContains(_destroyQueue, lowEnt)) {
                return lowEnt;
            }
            return INVALID_ENTITY;
        };

        std::size_t getPlayerDead(std::vector<EntityID> vector, EntityID id) {
            for (std::size_t i = 0; i < vector.size(); i++) {
                if (id == vector[i])
                    return i+1;
            }
            return -1;
        };

    private:
        std::shared_ptr<RL::Window> _window;
        std::shared_ptr<RL::Map> _map;
        RL::CollisionManager _colManager;
        UIManager _uiManager;
        std::vector<EntityID> _destroyQueue;
        std::shared_ptr<RL::SoundManager> _soundManager;
        bool _coinMode;
};

#endif /* !COLLISIONSYSTEM_HPP_ */
