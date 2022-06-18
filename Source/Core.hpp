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
#include "../menu_source/StartMenu.hpp"
#include "../menu_source/EndMenu.hpp"
#include "../menu_source/PauseMenu.hpp"
#include "../menu_source/Settings.hpp"
#include "../menu_source/CharacterSelect.hpp"
#include "../menu_source/MapSelect.hpp"

class Core {
    public:
        Core();
        ~Core();

        void startLoop();
        void restartGame();

    private:
        std::shared_ptr<RL::Window> _window;
        std::shared_ptr<RL::InputManager> _inputManager;
        std::shared_ptr<RL::Map> _map;
        std::shared_ptr<RL::SoundManager> _soundManager;
        Win::StartMenu *_startMenu = nullptr;
        Win::EndMenu *_endMenu = nullptr;
        Win::PauseMenu *_pauseMenu = nullptr;
        Win::Settings *_settings = nullptr;
        Win::CharacterSelect *_charSelec = nullptr;
        Win::MapSelect *_mapSelect = nullptr;
        Bomberman *_game = nullptr;
        int _prevS;
        int _prevM;
        int _screen;
};

#endif /* !CORE_HPP_ */
