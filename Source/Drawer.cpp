/*
** EPITECH PROJECT, 2022
** indie_studio
** File description:
** Drawer
*/

#include "Drawer.hpp"

RL::Drawer::Drawer(std::string name)
{
    this->_name = name;
}

RL::Drawer::~Drawer()
{
}

void RL::Drawer::draw_text(std::string text, Color color, int x, int y, Font font)
{
    //DrawText(text.c_str(), x, y, 20, color);

    //use this function when we get font handled
    DrawTextEx(font, text.c_str(), Vector2 {float(x), float(y)}, 20.0f, 2, color);
}

void RL::Drawer::draw_3D_model(Model model, float x, float y, float z)
{
    Vector3 position = { x, y, z };
    float scale = 0.1f;
    DrawModel(model, position, scale, WHITE);
    //DrawModelEx(model, position, (Vector3){ 1.0f, 0.0f, 0.0f }, rotationangle, (Vector3){ 0.1f, 0.1f, 0.1f }, WHITE);

}

void RL::Drawer::draw_2D_model(Texture2D texture, int x, int y)
{
    DrawTexture(texture, x, y, WHITE);
}

//to implement as argument, the path to or the actual map
// so that we can parse it and draw the 3dobjects on the grid at their coordinates
void RL::Drawer::draw_map(RL::Map Map)
{

    //mock cubes to be replaced with MAp._mapstaticAssets
    Vector3 WallBoxPos = { 0.0f, 0.0f, 0.0f };
    Vector3 WallBoxSize = { 1.0f, 1.0f, 1.0f };

    Vector2 size = {float(Map.getMapWidth()), float(Map.getMapDepth())};

    DrawGrid(10.0f, 1.0f);
    DrawPlane({0, 0 ,0}, size, BLUE);

    for (int i = 0; i < Map.getMapDepth(); i++) {
        for (int j = 0; j < Map.getMapWidth(); j++) {
            if (Map.getParsedMap()[i][j].tile == 1) {
                std::cout << "I SHOULD DRAW A WALL AT COORDINATES: " << i << " " << j << std::endl;
                WallBoxPos.x = i;
                WallBoxPos.z = j;
                DrawCube(WallBoxPos, WallBoxSize.x, WallBoxSize.y, WallBoxSize.z, RED);
            }
        }
    }
    std::cout <<"END MAP"<< std::endl;
}

void RL::Drawer::clearBackground()
{
    ClearBackground(RAYWHITE);
}

void RL::Drawer::begin3DMode(Camera camera)
{
    BeginMode3D(camera);
}

void RL::Drawer::end3DMode()
{
    EndMode3D();
}

void RL::Drawer::beginDrawing()
{
    BeginDrawing();
}

void RL::Drawer::endDrawing()
{
    EndDrawing();
}

