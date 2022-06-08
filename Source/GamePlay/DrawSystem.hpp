/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** DrawSystem
*/

#ifndef DRAWSYSTEM_HPP_
#define DRAWSYSTEM_HPP_

#include "ISystem.hpp"
#include "../Map.hpp"
#include "../Renderer.hpp"

class DrawSystem : public ISystem {
    public:
        DrawSystem(std::shared_ptr<EntityManager> em, std::shared_ptr<RL::Map> map, std::shared_ptr<RL::Renderer> drawer) : _map(map), _drawer(drawer) {
            _em = em;
        }
        ~DrawSystem() {};

        void update(float deltaTime, std::vector<EntityID> &playerIds) override {
            _map->draw_map();
            for (EntityID ent : EntityViewer<Pos, Sprite, CollisionObjectType>(*_em.get())) {
                Pos *objectPos = _em->Get<Pos>(ent);
                Sprite *objectSprite = _em->Get<Sprite>(ent);
                CollisionObjectType *objectType = _em->Get<CollisionObjectType>(ent);
                float z = translateObjectCoordinates(objectPos->y, _map->getMapDepth());
                if (*objectType != ITEM) {
                    objectSprite->model.setPosition(
                        translateObjectCoordinates(objectPos->x, _map->getMapWidth()),
                        0.5f + (z * 0.01f),
                        z
                    );
                }                
                objectSprite->model.draw();
            }
        }

        float translateObjectCoordinates(float pos, int borderSize)
        {
            float newpos = pos - (borderSize / 2);
            if (borderSize % 2 == 0)
                newpos += 0.5;
            return newpos;
        }

    private:
        std::shared_ptr<RL::Map> _map;
        std::shared_ptr<RL::Renderer> _drawer;
};

#endif /* !DRAWSYSTEM_HPP_ */
