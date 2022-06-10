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

            virtual DrawableType getType() const = 0;

        protected:
            DrawableType _type;
    };
}
