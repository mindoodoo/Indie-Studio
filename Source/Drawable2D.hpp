/*
** EPITECH PROJECT, 2022
** Drawable2D.hpp
** File description:
** .
*/

#pragma once

#include <raylib.h>
#include <string>
#include <stdexcept>
#include <sys/stat.h>

#include "IDrawable.hpp"
#include "RaylibTypeEncaps.hpp"

namespace RL {
    class Drawable2D: public IDrawable {
        public:
            Drawable2D(std::string assetPath);
            ~Drawable2D();

            // IDrawable methods
            void draw();
            // void reset();

            // Image Loading methods
            void loadImage(std::string assetPath);

            // Getters and setters
            bool isImageLoaded() const;

        protected:
            Vector3i _position = {0, 0, 0};

            bool _imageLoaded;
            Image _img;
            Texture2D _texture;
    };
}
