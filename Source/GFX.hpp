/*
** EPITECH PROJECT, 2022
** indie_studio
** File description:
** GFX
*/

#pragma once

#include <string>
#include "raylib.h"

class GFX {
    public:
        GFX(std::string title);
        ~GFX();

        //settings methods
        void set_window_size(int width, int height);

        //clear and refresh methods
        void clearWindow();

        //drawing methods
        void drawText(std::string text, int x, int y, int fontsize, CLITERAL(Color) color);

    protected:
    private:
        int _screenWidth;
        int _screenHeight;
        std::string _title;
};

