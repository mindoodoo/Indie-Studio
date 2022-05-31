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

typedef struct
{
    int tile;
    int orientation;
} gfx_tile_t;

namespace RL {
    class Map {
    public:
        Map(std::string mapCSVPath);
        ~Map();
        std::vector<std::vector<gfx_tile_t>> parseMap(const std::string &path);

        //getters
        int getMapWidth();
        int getMapDepth();
        std::vector<std::vector<gfx_tile_t>> getParsedMap();


    private:
        std::vector<std::vector<gfx_tile_t>> _parsedMap;
        //std::vector<IDRAWABLE_3DMODEL> _mapStaticAssets;
        std::vector<Model> _mapStaticAssets;
        int mapWidth;
        int mapDepth;
    };
}