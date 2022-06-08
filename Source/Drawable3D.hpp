/*
** EPITECH PROJECT, 2022
** indie_studio
** File description:
** Drawable3D
*/

#pragma once

#include <iostream>
#include <raylib.h>
#include <string>
#include <stdexcept>
#include <sys/stat.h>

#include "IDrawable.hpp"
//#include "RaylibTypeEncaps.hpp"



namespace RL {
    enum ModelType {
        MCGUYVER,
        WALL,
        CRATE,
        MODEL,
        FLOOR,
        POWER
    };


    class Drawable3D: public IDrawable {
        public:
            Drawable3D(std::string texturePath, std::string modelPath, std::string animationPath, float scale, ModelType type);
            ~Drawable3D();

            // IDrawable methods
            void draw();
            void drawPower();
            // void reset();

            // Image Loading / Manipulation methods
            void load3DModel(std::string texturePath, std::string modelPath, std::string animationPath);
            void unloadAll();
            void resize(float newScale);

            // Animation
            void loadAnimation(std::string path);
            void unloadAnimation();
            void updateModelsAnimation();
            void resetAnimSequence();
            void setCurrentAnim(int anim);
            int getCurrentAnim() const;

            bool isAnimLoaded() const;

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
            int up;

             // Animation
            ModelAnimation *_animations;
            int _currentAnim = 0;
            int _currentFrame = 0;
            unsigned int _animCount;
            bool _animationLoaded = false;
    };
}