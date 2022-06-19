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
#include "deque"

#include "../Raylib/Drawables/Drawable3D.hpp"
#include "../Raylib/RaylibTypeEncaps.hpp"
#include "../ECS/ECS.hpp"

typedef std::pair<size_t, size_t> coordinates_t;

enum UserInput {
    LAY_BOMB = -6,
    LAY_BOMB2 = 103,
    CLOSED_WINDOW = -5,
    UP = -4,
    LEFT = -3,
    DOWN = -2,
    RIGHT = -1,
    UP2 = 119,
    LEFT2 = 97,
    DOWN2 = 115,
    RIGHT2 = 100,
    NONE = -7,
    ESCAPE = -8
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
    AI,
    MONSTER,
    BOMB,
    EXPLOSION
};

enum ItemType {
    SPEED_UP = 's',
    BOMB_UP = 'b',
    FIRE_UP = 'f',
    WALLPASS = 'w'
};

enum PlayerNumber {
    One = 0,
    Two = 1
};

enum ExplosionDirection {
    Vertical = 0,
    Horizontal = 1
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

struct UIPos {
    int x;
    int y;
};

struct UiContinue {
    bool continueToRight;
};

struct Blocking {
    EntityID id;
    bool isBlocking;
};

struct BombProperty {
    std::vector<Blocking> blockingForPlayer;
};

struct Pos {
    float x;
    float y;
    float z;

    bool operator==(Pos &position) {
        if (this->x == position.x && \
            this->y == position.y && \
            this->z == position.z)
            return true;
        return false;
    }
};

struct Velocity {
    float x;
    float y;
    float z;

    Velocity operator*(const float &factor) {
        Velocity vel = Velocity();
        vel.x = this->x * factor;
        vel.y = this->y * factor;
        vel.z = this->z * factor;
        return vel;
    };

    Velocity operator+(const float &factor) {
        Velocity vel = Velocity(*this);
        if (this->x)
            vel.x = this->x + factor;
        if (this->y)
            vel.y = this->y + factor;
        if (this->z)
            vel.z = this->z + factor;
        return vel;
    };
};

enum TargetType {
    CRATE_TARGET,
    ITEM_TARGET,
    PLAYER_TARGET,
    BOMB_TARGET,
    RANDOM
};

struct AIData {
    bool detectedBomb;
    Pos target;
    TargetType targetType;
    int scanRadius;
    std::deque<coordinates_t> path;
    std::vector<int> blockingTiles;
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

typedef struct
{
    int tile;
    int orientation;
} gfx_tile_t;



#endif /* !COMPONENTS_HPP_ */
