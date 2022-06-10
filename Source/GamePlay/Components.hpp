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

#include "../Raylib/Drawables/Drawable3D.hpp"
#include "../Raylib/RaylibTypeEncaps.hpp"

enum UserInput {
    LAY_BOMB = -6,
    CLOSED_WINDOW = -5,
    UP = -4,
    LEFT = -3,
    DOWN = -2,
    RIGHT = -1,
    NONE
};

enum MapTranslation {
    UNKNOWN = -1,
    PATH = 0,
    WALL = 1,
    BREAKABLE_OBJECT = 2
};

// dont change order, it defines their dying priority
enum CollisionObjectType {
    ITEM,
    BREAKABLE_BLOCK,
    PLAYER,
    MONSTER,
    BOMB
};

enum PlayerNumber {
    One = 0,
    Two = 1
};

struct Level {
    std::size_t level;
};

struct Skillset {
    std::size_t bombUp;
    std::size_t speedUp;
    std::size_t fireUp;
    bool wallPass;

    Skillset operator+=(const Skillset &other) {
        bombUp += other.bombUp;
        speedUp += other.speedUp;
        fireUp += other.fireUp;
        if (!wallPass && other.wallPass)
            wallPass = true;
        return *this;
    };
};

struct BombCapacity {
    std::size_t totalAmount;
    std::size_t curCapacity;
};

struct BombOwner {
    EntityID id;
};

struct Pos {
    float x;
    float y;
    float z;
};

struct Velocity {
    float x;
    float y;
    float z;

    Velocity operator*(const float &factor) {
        this->x *= factor;
        this->y *= factor;
        this->z *= factor;  // is it necessary to change the z coordinate?
        return *this;
    }
};


struct Input {
    UserInput pressedKey; // walk in direction, lay bombs
    // user power ups
};

struct Score {
    std::size_t score;
};

struct Health {
    int health;
};

// ?
struct Sprite {
    RL::Drawable3D *model;
};

// replace by marc map
struct Map {
    std::vector<std::vector<int>> map;
};


#endif /* !COMPONENTS_HPP_ */
