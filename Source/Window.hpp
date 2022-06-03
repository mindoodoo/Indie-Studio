/*
** EPITECH PROJECT, 2022
** indie_studio
** File description:
** Window
*/

#pragma once

#include <iostream>
#include <string>
#include <raylib.h>
#include "Logger.hpp"
//#include "RaylibTypeEncaps.hpp"

namespace RL {
    class Window {
    public:
        Window(std::string title, Vector2 dimensions = {1920, 1080},
               bool initLater = false);
        ~Window();

        // Init and Close Methods
        void init();
        void init(Vector2 dimensions, std::string title);
        void close();

        // Display Methods
        void clearWindow(Color color);

        // Setters
        void setDimensions(const Vector2 &dimensions);
        void setTitle(const std::string &title);

        // Getters
        const Vector2 &getDimensions() const;
        const std::string &getTitle() const;
        bool isWindowOpen();
        bool checkWindowOpen() const;

        const Camera &getCamera() const;

    private:

        Vector2 _dimensions;
        Camera _camera;

        Logger _logger;
        std::string _title;
        bool _windowOpen;
        
    };
}

