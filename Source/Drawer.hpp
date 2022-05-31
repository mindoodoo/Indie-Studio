/*
** EPITECH PROJECT, 2022
** indie_studio
** File description:
** Drawer
*/

#pragma once

#include <raylib.h>
#include <iostream>
#include "Map.hpp"


// how does the drawer work :
//Drawer.clear()
//Drawer.begin_drawing()
//Drawer.begin_MODE()    MODE= 2D or 3D
//Drawer.draw_XXX
//Draweer.end_MODE()

namespace RL {
    class Drawer {
        public:
            Drawer(std::string name);
            ~Drawer();
            void clearBackground();
            void draw_3D_model(Model model, float x, float y, float z);
            void draw_2D_model(Texture2D texture, int x, int y);
            void draw_map(RL::Map Map); //should take map class as parameter, map class containing  each tile and its asset
            float translateCoordinatestoWorld(int pos, int borderSize);
            void begin3DMode(Camera camera);
            void beginDrawing();
            void end3DMode();
            void endDrawing();
            void draw_text(std::string text, Color color, int x, int y, Font font); // temporary, should create text class with font and size

        private:
            std::string _name;
    };   
}

