/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** Settings
*/

#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_

// #include <raylib.h>
// #include <string>
// #include <vector>
// #include "../Source/InputManager.hpp"
// //#include "../Source/Window.hpp"
// #include "../Source/Renderer.hpp"
// #include "../Source/Map.hpp"
// #include "../Source/Drawable3D.hpp"
// #include "../Source/Drawable2D.hpp"
// #include "Button.hpp"

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
    class Settings {
        public:
            Settings(std::shared_ptr<RL::Window> Window, std::shared_ptr<RL::InputManager> InputManager, std::shared_ptr<RL::SoundManager> SoundManager);
            ~Settings();

            int openSettings(int prev);
            void drawSettings();

        protected:
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

#endif /* !SETTINGS_HPP_ */
