/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** UIManager
*/

#ifndef UIMANAGER_HPP_
#define UIMANAGER_HPP_

#include <memory>
#include "../GamePlay/Components.hpp"
#include "Window.hpp"
#include "./Drawables/Drawable2D.hpp"

class UIManager {
    public:
        UIManager(std::shared_ptr<RL::Window> window);
        ~UIManager();

        void createBombUp(UIPos uiPos, int amount);
        void createFireUp(UIPos uiPos, int amount);
        void createSpeedUp(UIPos uiPos, int amount);
        void createWallPass(UIPos uiPos);

    private:
        std::shared_ptr<RL::Window> _window;
        std::vector<RL::Drawable2D *> _allIcons;
};

#endif /* !UIMANAGER_HPP_ */
