/*
** EPITECH PROJECT, 2022
** indie_studio
** File description:
** Scene
*/
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Drawable3D.hpp"
#include "Drawable2D.hpp"
#include "SoundManager.hpp"
#include <raylib.h>

namespace RL {
    class Scene {
    public:
        Scene(std::string sceneSpecsPath);
        ~Scene();

        void endScene();

        
        void moveCamera(Camera camera);
        void moveModels();

    protected:
    private:
        std::vector<RL::Drawable3D> _sceneModels;
        std::vector<RL::Drawable2D> _sceneSprites;
        bool _sceneIsOver = 0;
    };
}
