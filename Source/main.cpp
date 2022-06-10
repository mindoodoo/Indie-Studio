/*
** EPITECH PROJECT, 2022
** main.cpp
** File description:
** .
*/

#include <iostream>
#include "Drawable2D.hpp"
#include "Drawable3D.hpp"
#include "Window.hpp"
#include "InputManager.hpp"
#include "RaylibTypeEncaps.hpp"
#include "Cube.hpp"

int main()
{
    std::string modelPath = "RaylibTesting/Assets/3d_models/Guy/guy.iqm";
    std::string modelAnimPath = "RaylibTesting/Assets/3d_models/Guy/guyanim.iqm";
    std::string texturePath = "RaylibTesting/Assets/3d_models/Guy/guytex.png";

    RL::Window win("Bomberman");
    RL::Drawable3D *yo = new RL::Drawable3D(texturePath, modelPath, "", RL::MODEL);
    yo->loadAnimation(modelAnimPath);

    RL::Vector3f cameraPos = {100, 100, 100};
    win._camera.setPosition(cameraPos);

    cameraPos.x = 0;
    cameraPos.y = 30;
    cameraPos.z = 6;

    RL::Vector3f cubePos = {0, 0, 0};
    RL::Vector3f cubeSize = {5, 5, 5};
    
    RL::Cube *cube = new RL::Cube(cubeSize, cubePos, GREEN);

    win._camera.setPosition(cameraPos);
    win._camera.setRotation({ 0.1f, 0.0f, 0.0f });

    win.queueDrawable(yo);
    win.queueDrawable(cube);

    while (win.isWindowOpen()) {
        yo->updateModelsAnimation();
        win.displayDrawables();
        win.clearWindow(BLACK);
    }
}
