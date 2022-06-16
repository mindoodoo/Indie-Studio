/*
** EPITECH PROJECT, 2022
** indie
** File description:
** startmenu
*/

#ifndef STARTMENU_HPP_
#define STARTMENU_HPP_

#include <raylib.h>
#include <string>
#include <vector>
#include "InputManager.hpp"
#include "RaylibTypeEncaps.hpp"
#include "Drawables/Drawable2D.hpp"
#include "Window.hpp"
#include "Button.hpp"
#include "SoundManager.hpp"

namespace Win {
    class StartMenu {
        public:
            StartMenu(std::shared_ptr<RL::Window> Window, std::shared_ptr<RL::InputManager> InputManager, std::shared_ptr<RL::SoundManager> SoundManager);
            ~StartMenu();

            int openStartMenu();
            void drawMenu();
        private:
            std::shared_ptr<RL::Window> _window;
            std::shared_ptr<RL::InputManager> _inputManager;
            std::shared_ptr<RL::SoundManager> _soundManager;
            RL::Vector2f _mousePt;
            std::string _name;
            int _win_x;
            int _win_y;
            std::vector<std::string> _text;
            RL::Drawable2D *_bg = nullptr;
            std::vector<RL::Button> _btn;
    };
}


#endif /* !STARTMENU_HPP_ */
