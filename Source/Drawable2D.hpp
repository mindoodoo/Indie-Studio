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

            // Image Loading / Manipulation methods
            void loadImage(std::string assetPath);
            void unloadAll();
            void resize(Vector2i newSize);

            // Getters and setters
            bool isImageLoaded() const;
            void setTint(Color newTint);

        protected:
            // These initializations will not work
            Vector3i _position = {0, 0, 0};
            Vector2i _size = {0, 0};

            bool _imageLoaded = false;
            Image _img;
            Texture2D _texture;
            Color _tint = WHITE;
    };
}
