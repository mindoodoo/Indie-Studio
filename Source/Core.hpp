/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include <memory>
#include <vector>

#include "Raylib/Window.hpp"
#include "Raylib/InputManager.hpp"
#include "GameEngine/Map.hpp"
#include "GamePlay/Bomberman.hpp"
#include "GamePlay/ISystem.hpp"

class Core {
    public:
        Core();
        ~Core();

        void startLoop();

    private:
        std::shared_ptr<RL::Window> _window;
        std::shared_ptr<RL::InputManager> _inputManager;
        std::shared_ptr<RL::Map> _map;
        std::shared_ptr<RL::SoundManager> _soundManager;
        Bomberman *_game = nullptr;
};

#endif /* !CORE_HPP_ */
