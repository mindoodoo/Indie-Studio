/*
** EPITECH PROJECT, 2022
** indie_studio
** File description:
** GFX
*/

#include "Window.hpp"

// Construction / Destruction
Window::Window(std::string title, Vector2 dimensions, bool initLater)
        : _dimensions(dimensions), _windowOpen(false)
{
    if (!initLater) {
        InitWindow(this->_dimensions.x, this->_dimensions.y, title.c_str());
        this->_windowOpen = true;
    }
}

Window::~Window()
{
    CloseWindow();
}

// Method to init window if not init on construction
void Window::init()
{
    if (this->_windowOpen) {
        std::cout << "Window Encapsulation: Window is already initialized, doing nothing..." << std::endl;
        return;
    }
    InitWindow(this->_dimensions.x, this->_dimensions.y, this->_title.c_str());
    this->_windowOpen = true;
}

void Window::init(Vector2 dimensions, std::string title)
{
    if (this->_windowOpen) {
        std::cout << "Window Encapsulation: Window is already initialized, doing nothing..." << std::endl;
        return;
    }

    this->_dimensions = dimensions;
    this->_title = title;

    InitWindow(this->_dimensions.x, this->_dimensions.y, this->_title.c_str());
    this->_windowOpen = true;
}

void Window::close()
{
    if (!this->_windowOpen) {
        std::cout << "Window Encapsulation: No window is open, doing nothing..." << std::endl;
        return;
    }

    CloseWindow();
    this->_windowOpen = false;
}

// Display Methods
void Window::clearWindow(Color color)
{
    if (!this->_windowOpen) {
        std::cout << "Window Encapsulation: No window is open, doing nothing..." << std::endl;
        return;
    }
    ClearBackground(color);
}

// Setters
void Window::setDimensions(const Vector2 &dimensions)
{
    if (this->_windowOpen)
        std::cout << "Window Encapsulation: Window is already open, changes will only apply if restarted" << std::endl;
    this->_dimensions = dimensions;
}

void Window::setTitle(const std::string &title)
{
    if (this->_windowOpen)
        std::cout << "Window Encapsulation: Window is already open, changes will only apply if restarted" << std::endl;
    this->_title = title;
}

// Getters
const Vector2 &Window::getDimensions() const
{
    return this->_dimensions;
}

const std::string &Window::getTitle() const
{
    return this->_title;
}

bool Window::isWindowOpen() const
{
    return this->_windowOpen;
}