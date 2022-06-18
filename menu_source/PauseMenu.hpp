/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** PauseMenu
*/

#ifndef PAUSEMENU_HPP_
#define PAUSEMENU_HPP_

#include <raylib.h>
#include <string>
#include <vector>
#include "InputManager.hpp"
#include "RaylibTypeEncaps.hpp"
#include "Drawables/Drawable2D.hpp"
#include "Window.hpp"
#include "Button.hpp"
#include "SoundManager.hpp"
#include "../Source/Savegame/SaveManager.hpp"

namespace Win {
    class PauseMenu {
        public:
            PauseMenu(std::shared_ptr<RL::Window> Window, std::shared_ptr<RL::InputManager> InputManager, std::shared_ptr<RL::SoundManager> SoundManager, std::shared_ptr<RL::SaveManager> SaveManager);
            ~PauseMenu();

            int openPauseMenu();
            void drawPauseMenu();
        private:
            std::shared_ptr<RL::InputManager> _inputManager;
            std::shared_ptr<RL::SoundManager> _soundManager;
            std::shared_ptr<RL::SaveManager> _saveManager;
            std::shared_ptr<RL::Window> _window;
            RL::Vector2f _mousePt;
            std::string _name;
            int _win_x;
            int _win_y;
            std::vector<std::string> _text;
            RL::Drawable2D *_bg = nullptr;
            std::vector<RL::Button> _btn;
    };
}

#endif /* !PAUSEMENU_HPP_ */
