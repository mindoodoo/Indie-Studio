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
#include "RaylibTypeEncaps.hpp"

namespace RL {
    class Window {
    public:
        Window(std::string title, Vector2i dimensions = {1920, 1080},
               bool initLater = false);
        ~Window();

        // Init and Close Methods
        void init();
        void init(Vector2i dimensions, std::string title);
        void close();

        // Display Methods
        void clearWindow(Color color);

        // Setters
        void setDimensions(const Vector2i &dimensions);
        void setTitle(const std::string &title);

        // Getters
        const Vector2i &getDimensions() const;
        const std::string &getTitle() const;
        bool isWindowOpen() const;

    private:
        bool checkWindowOpen() const;

        Vector2i _dimensions;

        Logger _logger;
        std::string _title;
        bool _windowOpen;
        
    };
}

