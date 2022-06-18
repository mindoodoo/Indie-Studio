/*
** EPITECH PROJECT, 2022
** Project
** File description:
** Description
*/

#pragma once

#include "../GameEngine/Map.hpp"
#include <algorithm>
#include <valarray>
#include <iostream>
#include <stack>
#include <cmath>
#include <cstddef>
#include <string>
#include <queue>


class Node
{
    public:
        Node(Node *parent, coordinates_t position);

        Node *parent;

        coordinates_t position;

        int g;
        int h;
        int f = 0;
};

std::deque<coordinates_t> calculateAStar(coordinates_t start, coordinates_t end,
    std::vector<std::vector<gfx_tile_t>> map, std::vector<int> _blockingTiles);
std::deque<coordinates_t> avoidBomb(coordinates_t start, coordinates_t bombPos, int bombRadius,
    std::vector<std::vector<gfx_tile_t>> map, std::vector<int> _blockingTiles);

bool operator==(Node y, Node x);
