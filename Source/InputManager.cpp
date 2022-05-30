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
    return(GetCharPressed());
}

