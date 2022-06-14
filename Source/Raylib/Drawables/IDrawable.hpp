/*
** EPITECH PROJECT, 2022
** IDrawable.hpp
** File description:
** .
*/

#pragma once

#include <iostream>
#include <raylib.h>
#include <string>
#include <stdexcept>
#include <sys/stat.h>

#include "../../ECS/ECS.hpp"
#include "../RaylibTypeEncaps.hpp"

namespace RL {
    // Drawable type
    // Needs to be set in order for the drawable to be able to be queued in the Window
    enum DrawableType {
        Type3D,
        Type2D
    };

    // Interface base class for every drawable
    class IDrawable {
        public:
            virtual ~IDrawable() = default;

            // Function called by the Window to draw
            // Should NOT contain BeginDrawing(), EndDrawing() etc...
            virtual void draw() = 0;
            unsigned long long id = INVALID_ENTITY;
            virtual DrawableType getType() const = 0;
            virtual bool isHidden() const = 0;

        protected:
            DrawableType _type;
            bool _hidden = false;
    };
}
