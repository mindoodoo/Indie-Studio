/*
** EPITECH PROJECT, 2022
** indie_studio
** File description:
** Drawable3D
*/

#pragma once

#include <raylib.h>
#include <iostream>

enum ModelType {
    CUBE,
    MODEL
};

namespace RL {
    class Drawable3D {
        public:
            Drawable3D(std::string name, std::string modelPath, std::string texturePath);
            ~Drawable3D();

        private:
            std::string _name;
            Model _3DModel;
            Texture _3DTexture;
            BoundingBox _3DModelBox;
            ModelType _modelType;
    };
}

