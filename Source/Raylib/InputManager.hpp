/*
** EPITECH PROJECT, 2022
** indie_studio
** File description:
** InputManager
*/

#pragma once

#include <string> 
#include <raylib.h>
#include <iostream>
#include <thread>
#include <queue>
#include "RaylibTypeEncaps.hpp"


namespace RL {
    class InputManager {
    public:
        InputManager();
        ~InputManager();

        // Get input
        int recordInput();
        void recordInputs();
        void popInputs();
        bool playerHasPressedKeyAsChar(int key); // use like this : pHPKAC('p') or pHPKAC('w') or pHPKAC('-4') for up arrow

        std::vector<int> getInputs();
        RL::Vector2f getMousePosition();
        bool isMouseLeftClicked();
        bool isMouseRightClicked();

    private:
        std::string _name;
        std::vector<int> _inputQueue;
    };    
}