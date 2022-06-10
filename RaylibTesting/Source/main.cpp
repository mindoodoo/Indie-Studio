/*
** EPITECH PROJECT, 2022
** newMain.cpp
** File description:
** .
*/

// g++ newMain.cpp Drawable2D.cpp Renderer.cpp Window.cpp Logger.cpp -std=c++20 -L ./lib/ -lraylib -ldl -pthread

#include <iostream>
#include "Drawable2D.hpp"
#include "Drawable3D.hpp"
#include "Window.hpp"
#include "InputManager.hpp"
#include "RaylibTypeEncaps.hpp"

int main()
{
    std::string modelPath = "../Assets/3d_models/Guy/guy.iqm";
    std::string modelAnimPath = "../Assets/3d_models/Guy/guyanim.iqm";
    std::string texturePath = "../Assets/3d_models/Guy/guytex.png";

    RL::Window win("New Window");
    // RL::Drawable2D *yay = new RL::Drawable2D("2d_models/FrogIcon/frog-prince.png");
    RL::Drawable3D *yo = new RL::Drawable3D(texturePath, modelPath, "", RL::MODEL);
    yo->loadAnimation(modelAnimPath);

    RL::Vector3f cameraPos;
    cameraPos.y = 10;
    cameraPos.z = 10;
    cameraPos.x = 10;

    win._camera.setPosition(cameraPos);
    win._camera.setRotation({ 90.0f, 100.0f, 0.0f });

    // std::this_thread::sleep_for(std::chrono::seconds(1));
    // win.queueDrawable(yay);
    win.queueDrawable(yo);
    // yo->setScale(0.1);
    while (win.isWindowOpen()) {
        yo->updateModelsAnimation();
        win.displayDrawables();
        win.clearWindow(BLACK);
        // win.clearWindow(WHITE);
        // yay.draw();
        // yo.draw();
        // if (im.isMouseLeftClicked())
        //     yay.resize(RL::Vector2i(50, 50));
    }
}