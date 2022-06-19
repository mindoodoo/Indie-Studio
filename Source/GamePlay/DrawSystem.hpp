/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** DrawSystem
*/

#ifndef DRAWSYSTEM_HPP_
#define DRAWSYSTEM_HPP_

#include "ISystem.hpp"
#include "../GameEngine/Map.hpp"
#include "../Raylib/RaylibTypeEncaps.hpp"

class DrawSystem : public ISystem {
    public:
        DrawSystem(std::shared_ptr<EntityManager> em, std::shared_ptr<RL::Map> map) : _map(map) {
            _em = em;
        }
        ~DrawSystem() {};

        void update(float deltaTime, std::vector<EntityID> &playerIds, std::vector<EntityID> &aiBombLaying, std::vector<std::size_t> &deadPlayers, int &maxCoins) override {
            borderWidth = _map->getMapWidth() / 2;
            borderDepth = _map->getMapDepth() / 2;
            widthEven = (_map->getMapWidth() % 2 == 0);
            depthEven = (_map->getMapDepth() % 2 == 0);
            // _map->draw_map();
            for (EntityID ent : EntityViewer<Pos, Sprite, CollisionObjectType>(*_em.get())) {
                Pos *objectPos = _em->Get<Pos>(ent);
                Sprite *objectSprite = _em->Get<Sprite>(ent);
                CollisionObjectType type = *_em->Get<CollisionObjectType>(ent);
                if (type != ITEM) {
                    objectSprite->model->setPosition((RL::Vector3f){
                        translateObjectCoordinates(objectPos->x, borderWidth, widthEven),
                        0.5f,
                        translateObjectCoordinates(objectPos->y, borderDepth, depthEven)
                    });
                }
                if (type == PLAYER || type == AI || type == EXPLOSION)            
                    objectSprite->model->updateModelsAnimation();
                // objectSprite->model.draw();
            }
        }

        float translateObjectCoordinates(float pos, int borderSize, bool even)
        {
            float newpos = pos - (borderSize);
            if (even)
                newpos += 0.5;
            return newpos;
        }

    private:
        std::shared_ptr<RL::Map> _map;
        int borderWidth;
        int borderDepth;
        bool widthEven;
        bool depthEven;
};

#endif /* !DRAWSYSTEM_HPP_ */
