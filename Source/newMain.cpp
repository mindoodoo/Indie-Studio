/*
** EPITECH PROJECT, 2022
** newMain.cpp
** File description:
** .
*/

// g++ newMain.cpp Drawable2D.cpp Renderer.cpp Window.cpp Logger.cpp -std=c++20 -L ./lib/ -lraylib -ldl -pthread

#include "Drawable2D.hpp"
#include "Window.hpp"
#include "InputManager.hpp"
#include "RaylibTypeEncaps.hpp"

int main()
{
    RL::Window win("New Window");
    RL::Drawable2D yay("2d_models/FrogIcon/frog-prince.png");
    RL::InputManager im("Fuck these names my guy");
    
    while (win.isWindowOpen()) {
        win.clearWindow(WHITE);
        yay.draw();
        if (im.isMouseLeftClicked())
            yay.resize(RL::Vector2i(50, 50));
    }
}