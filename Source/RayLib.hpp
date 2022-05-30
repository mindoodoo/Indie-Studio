/*
** EPITECH PROJECT, 2022
** indie_studio
** File description:
** RayLib
*/

#pragma once

#include "Window.hpp"
#include "InputManager.hpp"

class RayLib {
    public:
        RayLib();
        ~RayLib();

    private:
        RL::InputManager _inputManager;
        RL::Window _window;

};
