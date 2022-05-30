/*
** EPITECH PROJECT, 2022
** indie_studio
** File description:
** Drawer
*/

#pragma once

#include <raylib.h>
#include <iostream>


namespace RL {
    class Drawer {
        public:
            Drawer(std::string name);
            ~Drawer();
            void draw_3D_model(Model model, float x, float y, float z);
            void draw_2D_model(int twodmodeltemplatearg, int x, int y);
            void draw_map();
            void draw_text(std::string text);

        private:
        std::string _name;
    };   
}

