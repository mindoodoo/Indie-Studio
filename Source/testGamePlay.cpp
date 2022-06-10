#include <iostream>
#include <raylib.h>
#include "Raylib/InputManager.hpp"
#include "Raylib/Window.hpp"
#include "GameEngine/Map.hpp"
#include "Raylib/Drawables/Drawable3D.hpp"
#include "Raylib/Drawables/Drawable2D.hpp"
#include "GamePlay/Bomberman.hpp"

int counter;

int main(void)
{
    std::shared_ptr<RL::Window> Window = std::make_shared<RL::Window>("TESTMAIN");
    //for everything to work, we need to init everything else AFTER THE WINDOW
    std::shared_ptr<RL::InputManager> InputManager = std::make_shared<RL::InputManager>();
    std::shared_ptr<RL::Map> Map = std::make_shared<RL::Map>("./RaylibTesting/Assets/Maps/TestMap/test.csv", "./RaylibTesting/Assets/Maps/TestMap/TEST_WALL.png", "./RaylibTesting/Assets/Maps/TestMap/Floor.png", "./RaylibTesting/Assets/Maps/TestMap/crate.png" );

    SetTargetFPS(60);

    RL::Vector3f cameraPos(0, 15, 8);

    Window->_camera.setPosition(cameraPos);
    Window->_camera.setRotation({0.0f, 1.0f, 0.0f });

    Bomberman game(Window, InputManager, Map);
    game.runFrame();

    Window->close();
    return 0;
}
