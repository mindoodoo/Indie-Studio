/*
** EPITECH PROJECT, 2022
** indie_studio
** File description:
** Map
*/

#pragma once

#include <raylib.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>
#include <cstring>
#include "Drawable3D.hpp"

typedef struct
    {
        int tile;
        int orientation;
    } gfx_tile_t;

namespace RL {
    
    class Map {
    public:
        Map(std::string mapCSVPath, std::string wallTexturePath, std::string floorTexturePath, std::string crateTexturePath);
        ~Map();
        std::vector<std::vector<gfx_tile_t>> parseMap(const std::string &path);

        //random crate generator
        void generate_all_crates();

        //Drawer
        void draw_map();

        //transformer mapcoord to 3d coord
        float translateCoordinatestoWorld(int pos, int borderSize);

        //getters
        int getMapWidth();
        int getMapDepth();
        std::vector<std::vector<gfx_tile_t>> getParsedMap();
        RL::Drawable3D getwallModel();


    private:
        std::vector<std::vector<gfx_tile_t>> _parsedMap;
        //std::vector<RL::Drawable3D> _mapStaticAssets;
        RL::Drawable3D _floorModel;
        RL::Drawable3D _wallModel;
        RL::Drawable3D _crateModel;
        std::string _wallTexturepath;
        int mapWidth;
        int mapDepth;
    };
}