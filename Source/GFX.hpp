/*
** EPITECH PROJECT, 2022
** indie_studio
** File description:
** GFX
*/

#pragma once

#include <iostream>
#include <string>
#include "raylib.h"

class GFX {
    public:
        GFX(std::string title);
        ~GFX();

        //settings methods
        void init();
        void set_window_size(int width, int height);
        void setCameraPosition(Vector3 camPos, Vector3 camTar, Vector3 camHeight, float camFov);
        void begin3D();
        void end3D();
        void closeWindow();

        //getting methods
        int getWindowWidth();
        int getWindowHeight();
        std::string getWindowTitle();
        Camera getCamera();

        //clear and refresh methods
        void clearWindow();

        //drawing methods
        void drawText(std::string text, int x, int y, int fontsize, CLITERAL(Color) color);
        void draw3DObject();

    protected:
    private:
        int _screenWidth;
        int _screenHeight;
        std::string _title;
        Camera _camera;
};

