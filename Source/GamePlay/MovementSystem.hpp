/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** MovementSystem
*/

#ifndef MOVEMENTSYSTEM_HPP_
#define MOVEMENTSYSTEM_HPP_

#include "ISystem.hpp"

class MovementSystem : public ISystem {
    public:
        MovementSystem(std::shared_ptr<EntityManager> em, Map map) {
            _em = em;
            _map = map;
        };
        ~MovementSystem() {};

        void update(float deltaTime) override {
            // use deltaTime
            for (EntityID ent : EntityViewer<Pos, Input>(*_em.get())) {
                Pos* playerPos = _em->Get<Pos>(ent);
                Input* playerMovement = _em->Get<Input>(ent);

                switch (playerMovement->pressedKey) {
                    case UP:
                        moveUp(playerPos);
                        break;
                    case DOWN:
                        moveDown(playerPos);
                        break;
                    case LEFT:
                        moveLeft(playerPos);
                        break;
                    case RIGHT:
                        moveRight(playerPos);
                        break;
                }
            }
        };

        // check for collision with objects in other system
        void moveLeft(Pos *pos)
        {
            if (pos->x > 0 && _map.map[pos->y][pos->x - 1] == PATH)
                pos->x -= 1;
        };

        void moveRight(Pos *pos)
        {
            if (pos->x + 1 < _map.map[pos->y].size() && _map.map[pos->y][pos->x + 1] == PATH)
                pos->x += 1;
        };

        void moveUp(Pos *pos)
        {
            if (pos->y > 0 && _map.map[pos->y - 1][pos->x] == PATH)
                pos->y -= 1;
        };

        void moveDown(Pos *pos)
        {
            if (pos->y + 1 < _map.map.size() && _map.map[pos->y + 1][pos->x] == PATH)
                pos->y += 1;
        };

    private:
        Map _map;
};

#endif /* !MOVEMENTSYSTEM_HPP_ */
