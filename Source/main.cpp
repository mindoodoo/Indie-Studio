#include <iostream>
#include <raylib.h>
#include "InputManager.hpp"
#include "Window.hpp"
#include "Renderer.hpp"
#include "Map.hpp"
#include "Drawable3D.hpp"
#include "Drawable2D.hpp"
#include "GamePlay/Bomberman.hpp"

int counter;

float translateCoordinatestoWorld(int pos, int borderSize)
{
    float newpos = pos - (borderSize / 2);
    if (borderSize % 2 == 0)
        newpos += 0.5;
    return newpos;
}

bool do_collision_walls(RL::Drawable3D Model, int i, int j , RL::Map Map)
{
    float x = translateCoordinatestoWorld(j, Map.getMapWidth());
    float z = translateCoordinatestoWorld(i, Map.getMapDepth());
    if (CheckCollisionSpheres(Model.getPosition(), 0.5f, Vector3{x, 0.5f, z}, 0.5f))
        return true;
    return false;
}

int main(void)
{
    int keystroke;
    bool collision = false;
    const int screenWidth = 800;
    const int screenHeight = 450;

    std::shared_ptr<RL::Window> Window = std::make_shared<RL::Window>("TESTMAIN");
    //for everything to work, we need to init everything else AFTER THE WINDOW
    std::shared_ptr<RL::InputManager> InputManager = std::make_shared<RL::InputManager>("TESTINPUTMANAGER");
    std::shared_ptr<RL::Renderer> Drawer = std::make_shared<RL::Renderer>("TESTDRAWER");
    std::shared_ptr<RL::Map> Map = std::make_shared<RL::Map>("./Source/Maps/TestMap/test.csv", "./Source/Maps/TestMap/TEST_WALL.png", "./Source/Maps/TestMap/Floor.png" );

    RL::Drawable2D playerIcon("./Source/2d_models/FrogIcon/frog-prince.png");
    Vector2 newSize = {50, 50};
    playerIcon.resize(newSize);
    playerIcon.setPosition(80, 150, 0);

    int text_x = playerIcon.getPosition().x;
    int text_y = playerIcon.getPosition().y;
    int player_height = playerIcon.getTexture().height;
    Font SquidFont = LoadFontEx("./Source/Fonts/Game_Of_Squids.ttf", 20, 0, 250);
    SetTargetFPS(60);

    Bomberman game(Window, InputManager, Map, Drawer);
    game.runFrame();

    Window->close();
    return 0;
}
