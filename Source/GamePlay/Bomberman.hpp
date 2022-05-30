/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** Bomberman
*/

#ifndef BOMBERMAN_HPP_
#define BOMBERMAN_HPP_

#include <vector>
#include "Player.hpp"

class Bomberman {
    public:
        Bomberman();
        ~Bomberman();

        void runFrame();
        void checkGameEnd();

    protected:
    private:
        UserInput _event;
        std::vector<Player> _player;
        Map _map;
        std::shared_ptr<EntityManager> _em;
};

#endif /* !BOMBERMAN_HPP_ */
