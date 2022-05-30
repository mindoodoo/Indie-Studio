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

void RL::Drawer::draw_3D_model(Model model, float x, float y, float z)
{
    Vector3 position = { x, y, z };
    float scale = 0.1f;
    DrawModel(model, position, scale, WHITE);
    //DrawModelEx(model, position, (Vector3){ 1.0f, 0.0f, 0.0f }, rotationangle, (Vector3){ 0.1f, 0.1f, 0.1f }, WHITE);

}

//to implement as argument, the path to or the actual map
// so that we can parse it and draw the 3dobjects on the grid at their coordinates
void RL::Drawer::draw_map()
{
    //to change with
    DrawGrid(20, 1.0f);
}

