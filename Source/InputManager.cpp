/*
** EPITECH PROJECT, 2022
** indie_studio
** File description:
** InputManager
*/

#include "InputManager.hpp"


RL::InputManager::InputManager(std::string name)
{
    this->_name = _name;
}

RL::InputManager::~InputManager()
{
}

int RL::InputManager::recordInput()
{
    if (IsKeyPressed(KEY_UP))
        return -4;
    if (IsKeyPressed(KEY_DOWN))
    return -2;
    if (IsKeyPressed(KEY_LEFT))
    return -3;
    if (IsKeyPressed(KEY_RIGHT))
    return -1;

    return GetCharPressed();
}

