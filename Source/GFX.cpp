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

    InitWindow(_screenWidth, _screenHeight, title.c_str());
}

GFX::~GFX()
{
    CloseWindow();
}

void GFX::set_window_size(int width, int height)
{
    this->_screenWidth = width;
    this->_screenHeight = height;
}

void GFX::clearWindow()
{
    ClearBackground(BLANK);
}

void GFX::drawText(std::string text, int x, int y, int fontsize, CLITERAL(Color) color)
{
    
}
