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

        void createBombUp(UIPos uiPos, int amount, bool continueToRight);
        void createFireUp(UIPos uiPos, int amount, bool continueToRight);
        void createSpeedUp(UIPos uiPos, int amount, bool continueToRight);
        void createWallPass(UIPos uiPos);
        void createCoin(UIPos uiPos, int amount, bool continueToRight);

    private:
        std::shared_ptr<RL::Window> _window;
        std::vector<RL::Drawable2D *> _allIcons;
        int offset;
};

#endif /* !UIMANAGER_HPP_ */
