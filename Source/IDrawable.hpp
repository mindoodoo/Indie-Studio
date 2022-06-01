/*
** EPITECH PROJECT, 2022
** IDrawable.hpp
** File description:
** .
*/

#pragma once

namespace RL {
    enum DrawableType {
        Type3D,
        Type2D
    };

    class IDrawable {
        public:
            virtual ~IDrawable() = default;

            virtual void draw() = 0;
            // virtual void reset() = 0; // Not sure about this one

        protected:
    };
}
