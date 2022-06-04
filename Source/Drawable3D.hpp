/*
** EPITECH PROJECT, 2022
** indie_studio
** File description:
** Drawable3D
*/

#pragma once

#include <raylib.h>
#include <string>
#include <stdexcept>
#include <sys/stat.h>

#include "IDrawable.hpp"
//#include "RaylibTypeEncaps.hpp"

#define MODEL_RADIUS = 0.45f

namespace RL {
    enum ModelType {
        WALL,
        CRATE,
        MODEL,
        FLOOR
    };


    class Drawable3D: public IDrawable {
        public:
            Drawable3D(std::string texturePath, std::string modelPath, float scale, ModelType type);
            ~Drawable3D();

            // IDrawable methods
            void draw();
            // void reset();

            // Image Loading / Manipulation methods
            void load3DModel(std::string texturePath, std::string modelPath);
            void unloadAll();
            void resize(float newScale);

            // Getters and setters
            bool isImageLoaded() const;
            void setTint(Color newTint);

            void setPosition(float x, float y, float z);
            Vector3 getPosition();

            Vector3 getBoxSize();

            Texture2D getTexture();

            void setBoundingBox();
            BoundingBox getBoundingBox();

        protected:
            // These initializations will not work
            Vector3 _position = {0, 0, 0};
            Vector3 _boxSize;

            bool _imageLoaded = false;
            Image _img;
            Texture2D _texture;
            Model _model;
            Color _tint = WHITE;
            float _scale;
            ModelType _type;
            BoundingBox _boundingBox;
    };
}