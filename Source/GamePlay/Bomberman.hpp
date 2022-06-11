/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** Bomberman
*/

#ifndef BOMBERMAN_HPP_
#define BOMBERMAN_HPP_

#include <vector>
#include "ISystem.hpp"
#include "MovementSystem.hpp"
#include "CollisionSystem.hpp"
#include "DrawSystem.hpp"
#include "../Raylib/Drawables/Drawable3D.hpp"
#include "../Raylib/InputManager.hpp"
#include "../GameEngine/Map.hpp"
#include "../Raylib/Window.hpp"
#include "Timer.hpp"

class Bomberman {
    public:
        Bomberman(std::shared_ptr<RL::Window> Window, std::shared_ptr<RL::InputManager> InputManager, std::shared_ptr<RL::Map> Map);
        ~Bomberman();

        void createPlayer(Pos pos);
        void createItem(Pos pos);
        void createMonster(Pos pos);
        void layBomb(EntityID playerid);
        void checkBombalive();
        bool createBomb(Pos pos, EntityID bombOwner);
        void checkInput();
        void runFrame();
        void startDrawScene();
        void stopDrawScene();
        void checkGameEnd();
        bool createExplosion(Pos pos, Skillset skills, EntityID bombOwner);
        void checkExplosionalive();

    protected:
    private:
        std::shared_ptr<RL::Window> _window;
        std::shared_ptr<RL::InputManager> _inputManager;
        std::shared_ptr<RL::Map> _map;
        std::vector<int> _event;
        std::vector<std::shared_ptr<ISystem>> _systems;
        std::vector<EntityID> _player;
        std::shared_ptr<EntityManager> _em;
};

float translateFigureCoordinates(float pos, int borderSize);

#endif /* !BOMBERMAN_HPP_ */
