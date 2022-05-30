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


namespace RL {
    class InputManager {
    public:
        InputManager(std::string name);
        ~InputManager();
        int recordInput();

    private:
        std::string _name;
    };    
}