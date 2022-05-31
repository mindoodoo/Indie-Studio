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


// -4 = UP ; -3 = LEFT ; -2 = DOWN ; -1 = RIGHT
int RL::InputManager::recordInput()
{
    if (IsKeyDown(KEY_UP))
        return -4;
    if (IsKeyDown(KEY_DOWN))
    return -2;
    if (IsKeyDown(KEY_LEFT))
    return -3;
    if (IsKeyDown(KEY_RIGHT))
    return -1;

    return GetCharPressed();
}


// RL::Vector2i RL::InputManager::getMousePosition()
// {
//     RL::Vector2i mousePosition;
//     mousePosition.x = GetMouseX();
//     mousePosition.y = GetMouseY();

//     return mousePosition;
// }

bool RL::InputManager::isMouseLeftClicked()
{
    return IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

}

bool RL::InputManager::isMouseRightClicked()
{
    return IsMouseButtonPressed(MOUSE_BUTTON_RIGHT);

}