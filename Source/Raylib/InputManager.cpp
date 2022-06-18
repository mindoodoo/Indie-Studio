/*
** EPITECH PROJECT, 2022
** indie_studio
** File description:
** InputManager
*/

#include "InputManager.hpp"

RL::InputManager::InputManager()
{
    SetExitKey(KEY_CAPS_LOCK);
}

RL::InputManager::~InputManager()
{
}

// -4 = UP ; -3 = LEFT ; -2 = DOWN ; -1 = RIGHT
void RL::InputManager::recordInputs()
{
    if (IsKeyDown(KEY_W))
        this->_inputQueue.emplace_back('w');
    if (IsKeyDown(KEY_A))
        this->_inputQueue.emplace_back('a');
    if (IsKeyDown(KEY_S))
        this->_inputQueue.emplace_back('s');
    if (IsKeyDown(KEY_D))
        this->_inputQueue.emplace_back('d');
    char pressedKey = GetCharPressed();
    if (pressedKey != 0)
        this->_inputQueue.emplace_back(pressedKey);

    if (IsKeyDown(KEY_UP))
        this->_inputQueue.emplace_back(-4);
    if (IsKeyDown(KEY_DOWN))
        this->_inputQueue.emplace_back(-2);
    if (IsKeyDown(KEY_LEFT))
        this->_inputQueue.emplace_back(-3);
    if (IsKeyDown(KEY_RIGHT))
        this->_inputQueue.emplace_back(-1);
    if (IsKeyPressed(KEY_SPACE))
        this->_inputQueue.emplace_back(-6);
    if (IsKeyPressed(KEY_ESCAPE))
        this->_inputQueue.emplace_back(-8);
    //std::this_thread::sleep_for(std::chrono::milliseconds(100)); // This should change
}


void RL::InputManager::popInputs()
{
    if (!this->_inputQueue.empty())
        this->_inputQueue.clear();
}

bool RL::InputManager::playerHasPressedKeyAsChar(int key)
{
    for (int i = 0; i < this->_inputQueue.size(); i++) {
            if (this->_inputQueue[i]== key)
                return true;
    }
    return false;        
}

std::vector<int> RL::InputManager::getInputs()
{
    return this->_inputQueue;
}


RL::Vector2f RL::InputManager::getMousePosition()
{
    RL::Vector2f mousePosition(GetMousePosition().x, GetMousePosition().y);
    return mousePosition;
}

bool RL::InputManager::isMouseLeftClicked()
{
    return IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    // Needs click position
}

bool RL::InputManager::isMouseRightClicked()
{
    return IsMouseButtonPressed(MOUSE_BUTTON_RIGHT);
    // Needs click position
}