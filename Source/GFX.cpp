/*
** EPITECH PROJECT, 2022
** indie_studio
** File description:
** GFX
*/

#include "GFX.hpp"


GFX::GFX(std::string title)
{
    _screenHeight = 600;
    _screenWidth = 800;
    _title = title;
    _camera = { 0 };
    _camera.position = (Vector3){ 0.0f, 15.0f, 15.0f };  // Camera position
    _camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    _camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    _camera.fovy = 45.0f;                                // Camera field-of-view Y
    _camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

    //InitWindow(_screenWidth, _screenHeight, title.c_str());
}

GFX::~GFX()
{
    //CloseWindow();
}

//Setting methods

void GFX::init()
{
    InitWindow(this->getWindowWidth(), this->getWindowHeight(), this->getWindowTitle().c_str());
}

void GFX::closeWindow()
{
    CloseWindow();
}

void GFX::set_window_size(int width, int height)
{
    this->_screenWidth = width;
    this->_screenHeight = height;
}

void GFX::setCameraPosition(Vector3 camPos, Vector3 camTar, Vector3 camHeight, float camFov)
{
    this->getCamera().position = camPos;
    this->getCamera().target = camTar;
    this->getCamera().up = camHeight;
    //this->getCamera().fovy = camFov;            this here doesnt work, using rvalue as lvalue
}

void GFX::begin3D()
{
    BeginMode3D(this->getCamera());
}

void GFX::end3D()
{
    EndMode3D();
}

//getting methods

int GFX::getWindowWidth()
{
    return _screenWidth;
}

int GFX::getWindowHeight()
{
    return _screenHeight;
}

std::string GFX::getWindowTitle()
{
    return _title;
}

Camera GFX::getCamera()
{
    return _camera;
}


//display functions

void GFX::clearWindow()
{
    ClearBackground(RAYWHITE);
}

void GFX::drawText(std::string text, int x, int y, int fontsize, CLITERAL(Color) color)
{
    DrawText(text.c_str(), x, y, fontsize, color);
}

void GFX::draw3DObject()
{
    // Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };
    // DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
    // DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);

    // Vector3 centerPos = {5.0f, 5.0f, 5.0f};
    // float radius = 3.0f;
    // DrawSphere(centerPos, radius, BLUE); 

    DrawGrid(20, 1.0f);

}