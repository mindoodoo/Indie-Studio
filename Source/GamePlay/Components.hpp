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
    LAY_BOMB,
    CLOSED_WINDOW,
    NONE
};

enum MapTranslation {
    UNKNOWN = 0,
    WALL = 1,
    PATH = 2,
    BREAKABLE_OBJECT = 3
};

// dont change order, it defines their dying priority
enum CollisionObjectType {
    ITEM,
    BREAKABLE_BLOCK,
    PLAYER,
    MONSTER,
    BOMB
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
};

struct Velocity {
    float x;
    float y;

    Velocity operator*(const float &factor) {
        this->x *= factor;
        this->y *= factor;
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
    std::string filePath;
};

// replace by marc map
struct Map {
    std::vector<std::vector<int>> map;
};

#endif /* !COMPONENTS_HPP_ */
