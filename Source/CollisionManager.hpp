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
#include "Drawable3D.hpp"
#include "Map.hpp"

namespace RL {
    class CollisionManager {
        public:
            CollisionManager();
            ~CollisionManager();

            bool collisionsWithWalls(Vector3 ModelPos,RL::Map Map);

            //the next is to be revised
            bool collisionsWithModels(Vector3 MovingPos, RL::Drawable3D Model2);

        private:
    };
}
