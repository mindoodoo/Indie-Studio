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
#include "../Drawable3D.hpp"
#include "../InputManager.hpp"
#include "../Map.hpp"
#include "../Renderer.hpp"
#include "../Window.hpp"

class Bomberman {
    public:
        Bomberman(std::shared_ptr<RL::Window> Window, std::shared_ptr<RL::InputManager> InputManager, std::shared_ptr<RL::Map> Map, std::shared_ptr<RL::Renderer> Drawer);
        ~Bomberman();

        void createPlayer(Pos pos);
        void createItem(Pos pos);
        void createMonster(Pos pos);
        void createBomb(Pos pos, EntityID bombOwner);
        void checkInput();
        void runFrame();
        void startDrawScene();
        void stopDrawScene();
        void checkGameEnd();

    protected:
    private:
        std::shared_ptr<RL::Window> _window;
        std::shared_ptr<RL::InputManager> _inputManager;
        std::shared_ptr<RL::Map> _map;
        std::shared_ptr<RL::Renderer> _drawer;
        std::vector<int> _event;
        std::vector<std::shared_ptr<ISystem>> _systems;
        std::vector<EntityID> _player;
        std::shared_ptr<EntityManager> _em;
};

#endif /* !BOMBERMAN_HPP_ */
