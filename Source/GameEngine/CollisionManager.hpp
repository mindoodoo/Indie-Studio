/*
** EPITECH PROJECT, 2022
** indie_studio
** File description:
** CollisionManager
*/

#pragma once

#include <iostream>
#include <string>
#include <raylib.h>
#include "RaylibTypeEncaps.hpp"
#include "Drawable3D.hpp"
#include "Map.hpp"

namespace RL {
    class CollisionManager {
        public:
            CollisionManager();
            ~CollisionManager();

            // Methods to check if collision
            bool collisionsWithWalls(RL::Vector3f ModelPos,RL::Map Map);
            bool collisionsWithCrates(RL::Vector3f ModelPos, RL::Map Map);
            bool collisionsWithModels(RL::Drawable3D Model1, RL::Drawable3D Model2);
            bool collisionsWithModels(RL::Vector3f ModelPos, RL::Drawable3D Model2);

        private:
    };
}
