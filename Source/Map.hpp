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
#include "./Drawables/Drawable3D.hpp"

typedef struct
{
    int tile;
    int orientation;
} gfx_tile_t;

namespace RL {
    class Map {
    public:
        Map(std::string mapCSVPath, std::string wallTexturePath);
        ~Map();
        std::vector<std::vector<gfx_tile_t>> parseMap(const std::string &path);

        //getters
        int getMapWidth();
        int getMapDepth();
        std::vector<std::vector<gfx_tile_t>> getParsedMap();


    private:
        std::vector<std::vector<gfx_tile_t>> _parsedMap;
        //std::vector<RL::Drawable3D> _mapStaticAssets;
        std::string _wallTexturepath;
        Texture2D _wallTexture;
        //std::vector<Model> _mapStaticAssets;
        int mapWidth;
        int mapDepth;
    };
}