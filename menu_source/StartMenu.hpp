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
#include "../Source/Savegame/SaveManager.hpp"
#include <chrono>
#include <thread>

namespace Win {
    class StartMenu {
        public:
            StartMenu(std::shared_ptr<RL::Window> Window, std::shared_ptr<RL::InputManager> InputManager, std::shared_ptr<RL::SoundManager> SoundManager, std::shared_ptr<RL::SaveManager> SaveManager);
            ~StartMenu();

            int openStartMenu();
            void drawMenu();
            int starIntro();
        private:
            std::shared_ptr<RL::Window> _window;
            std::shared_ptr<RL::InputManager> _inputManager;
            std::shared_ptr<RL::SoundManager> _soundManager;
            std::shared_ptr<RL::SaveManager> _saveManager;
            RL::Vector2f _mousePt;
            std::string _name;
            int _win_x;
            int _win_y;
            std::vector<std::string> _text;
            RL::Drawable2D *_bg = nullptr;
            std::vector<RL::Button> _btn;
            RL::Drawable2D *_intro;
    };
}


#endif /* !STARTMENU_HPP_ */
