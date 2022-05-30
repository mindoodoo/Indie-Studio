/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** Components
*/

#ifndef COMPONENTS_HPP_
#define COMPONENTS_HPP_

#include <memory>
#include <vector>

enum UserInput {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    CLOSED_WINDOW,
    NONE
};

enum MapTranslation {
    UNKNOWN = 0,
    WALL = 1,
    PATH = 2,
    BREAKABLE_OBJECT = 3
};

struct Pos {
    int x;
    int y;
};

struct Score {
    std::size_t score;
};

struct Health {
    int health;
};

// replace by marc map
struct Map {
    std::vector<std::vector<int>> map;
};

#endif /* !COMPONENTS_HPP_ */
