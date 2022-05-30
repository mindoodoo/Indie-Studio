/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** Player
*/

#include "Player.hpp"

Player::Player(std::shared_ptr<EntityManager> em, Pos pos)
{
    _id = em->CreateNewEntity();
    em->Assign<Pos>(_id, pos);
    em->Assign<Score>(_id, Score{0});
    em->Assign<Health>(_id, Health{100});
    _em = em;
}

Player::~Player()
{
}

void Player::movePlayer(UserInput event, Map map)
{
    switch (event) {
        case UP:
            moveUp(map);
            break;
        case DOWN:
            moveDown(map);
            break;
        case LEFT:
            moveLeft(map);
            break;
        case RIGHT:
            moveRight(map);
            break;
    }
}

void Player::moveLeft(Map map)
{
    Pos *pos = _em->Get<Pos>(_id);
    if (pos->x > 0 && map.map[pos->y][pos->x - 1] == PATH)
        pos->x -= 1;
};

void Player::moveRight(Map map)
{
    Pos *pos = _em->Get<Pos>(_id);
    if (pos->x + 1 < map.map[pos->y].size() && map.map[pos->y][pos->x + 1] == PATH)
        pos->x += 1;
};

void Player::moveUp(Map map)
{
    Pos *pos = _em->Get<Pos>(_id);
    if (pos->y > 0 && map.map[pos->y - 1][pos->x] == PATH)
        pos->y -= 1;
};

void Player::moveDown(Map map)
{
    Pos *pos = _em->Get<Pos>(_id);
    if (pos->y + 1 < map.map.size() && map.map[pos->y + 1][pos->x] == PATH)
        pos->y += 1;
};
