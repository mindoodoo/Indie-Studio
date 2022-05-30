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
#include "RaylibTypeEncaps.hpp"


namespace RL {
    class InputManager {
    public:
        InputManager();
        InputManager(std::string name);
        ~InputManager();
        int recordInput();
        Vector2i getMousePosition();

    private:
        std::string _name;
    };    
}