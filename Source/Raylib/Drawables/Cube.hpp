/*
** EPITECH PROJECT, 2022
** Cube.hpp
** File description:
** .
*/

#pragma once

#include "IDrawable.hpp"

namespace RL
{
    class Cube: public IDrawable {
        public:
            Cube(Vector3f size, Vector3f position, Color color = BLACK);
            ~Cube();

            void draw();
            void loadTexture(std::string path);
            void resetTexture();

            void setColor(Color color);
            void setPosition(Vector3f position);
            void setScale(float scale);
            void setRotation(Vector3f rotation);
            void setSize(Vector3f size);

            DrawableType getType() const;

        protected:
            Vector3f _position;
            Vector3f _rotation = {0, 0, 0};
            Vector3f _size;
            float _scale = 1;

            Color _color;

            bool _textureSet = false;
            std::string _texturePath;

            Image _image;
            Texture2D _texture;

            DrawableType _type;
    };
}
