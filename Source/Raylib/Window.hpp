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
#include <vector>
#include "GameEngine/Map.hpp"
#include "Logger/Logger.hpp"
#include "Camera.hpp"
#include "Raylib/Drawables/IDrawable.hpp"
#include "Raylib/Drawables/Drawable3D.hpp"
#include "RaylibTypeEncaps.hpp"

namespace RL {
    class Window {
    public:
        // Creation of window
        // By default, window is initialized immediately, but can be done later
        // by passing initLater = true
        Window(std::string title, Vector2i dimensions = {1920, 1080},
               bool initLater = false);
        ~Window();

        // Init and Close Methods
        void init(); // Init window, does nothing if already init
        void init(Vector2i dimensions, std::string title); // Same, but more args for flexibility
        void close(); // Closes window

        // Display Methods
        // Use WHITE, BLACK, etc... macros provided by raylib for color arg
        void clearWindow(Color color);

        // Add drawable to queue to be displayed when displayDrawables() is called
        void queueDrawable(IDrawable *drawable);
        void removeDrawable(IDrawable *drawable);
        
        // Display all 2D and 3D Drawables in queue
        void displayDrawables(Map map);

        // Misc
        // Checks if a window is initiated and prints if not
        bool checkWindowOpen() const;

        // Setters
        void setDimensions(const Vector2i &dimensions);
        void setTitle(const std::string &title);

        // Getters
        const Vector2i &getDimensions() const;
        const std::string &getTitle() const;

        // Check if window is initiated and checks if window should close
        bool isWindowOpen();

        Camera _camera;

    private:
        Vector2i _dimensions;

        // This may be inefficient as it may be duplicating all data
        std::vector<IDrawable*> _displayQueue3D;
        std::vector<IDrawable*> _displayQueue2D;

        Logger _logger;
        
        std::string _title;
        bool _windowOpen;
    };
}

