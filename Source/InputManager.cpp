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


RL::Vector2i RL::InputManager::getMousePosition()
{
    RL::Vector2i mousePosition;
    mousePosition.x = GetMouseX();
    mousePosition.y = GetMouseY();

    return mousePosition;
}

bool RL::InputManager::isMouseLeftClicked()
{
    return IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

}

bool RL::InputManager::isMouseRightClicked()
{
    return IsMouseButtonPressed(MOUSE_BUTTON_RIGHT);

}