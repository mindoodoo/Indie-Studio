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
#include <algorithm>
#include "GameEngine/Map.hpp"
#include "Logger/Logger.hpp"
#include "Camera.hpp"
#include "Raylib/Drawables/IDrawable.hpp"
#include "Drawables/Drawable3D.hpp"
#include "Drawables/Drawable2D.hpp"
#include "RaylibTypeEncaps.hpp"

typedef struct PlayerChoice {
    std::size_t Character;
    bool CPU;
    std::size_t playerOrder;

} PlayerChoice;

namespace RL {
    class Window {
    public:
        // Creation of window
        // By default, window is initialized immediately, but can be done later
        // by passing initLater = true
        Window(std::string title, Vector2i dimensions = {1200, 800},
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

        //Draw a 2Ddrawable by passing it as argument to
        void displayDrawable2D(RL::Drawable2D drawable);
        void clearDrawables();
        
        // Display all 2D and 3D Drawables in queue
        void displayDrawables(Map map, std::string text, int textX, int textY);

        // Draw some text on the window
        void draw_text(std::string text, Color color, int x, int y, Font font, float size); // temporary, should create text class with font and size


        // Misc
        // Checks if a window is initiated and prints if not
        bool checkWindowOpen() const;

        // Setters
        void setDimensions(const Vector2i &dimensions);
        void setTitle(const std::string &title);

        // Getters
        const Vector2i &getDimensions() const;
        const std::string &getTitle() const;
        const std::vector<RL::IDrawable*> get3Dqueue() const;

        Font getFont();
        Font getHeadFont();
        Font getTxtFont();

        // Check if window is initiated and checks if window should close
        bool isWindowOpen();

        void removeElemtfrom3Dqueue(int index);

        Camera _camera;

    private:
        Vector2i _dimensions;

        // This may be inefficient as it may be duplicating all data
        std::vector<IDrawable*> _displayQueue3D;
        std::vector<IDrawable*> _displayQueue2D;

        Logger _logger;
        
        std::string _title;
        bool _windowOpen;
        
        Font _windowFont;
        Font _headFont;
        Font _txtFont;
    };
}

