/*
** EPITECH PROJECT, 2022
** Drawable2D.hpp
** File description:
** .
*/

#pragma once

#include <string>
#include <stdexcept>
#include <sys/stat.h>

#include "IDrawable.hpp"

namespace RL {
    // Allows for the drawing of a 2D texture
    class Drawable2D: public IDrawable {
        public:
            // Arg is Path to .png
            Drawable2D(std::string assetPath);
            Drawable2D(Texture2D texture, int x, int y);
            ~Drawable2D();

            // IDrawable methods
            void draw();

            // Image Loading / Manipulation methods
            void loadImage(std::string assetPath);
            void unloadAll(); // Unload image and texture
            void resize(Vector2i newSize); // Resize image and update texture

            // Getters and setters
            bool isImageLoaded() const;
            void setTint(Color newTint); // Sets tint of texture

            void setPosition(float x, float y, float z);

            Vector3f getPosition();
            Texture2D getTexture();
            Color getTint();

            DrawableType getType() const;
            bool isHidden() const override;
            
        protected:
            Vector3f _position = {0, 0, 0};
            Vector2i _size = {0, 0};

            bool _imageLoaded = false;
            Image _img; // Image from which _texture is loaded
            Texture2D _texture; // Texture drawn on screen
            Color _tint = WHITE;

            DrawableType _type = Type2D;
    };
}
