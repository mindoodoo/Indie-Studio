/*
** EPITECH PROJECT, 2022
** indie_studio
** File description:
** GFX
*/

#include "Window.hpp"

// Construction / Destruction
Window::Window(std::string title, Vector2 dimensions, bool initLater)
        : _dimensions(dimensions), _windowOpen(false), _logger(Logger("WindowEncapsulation"))
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
        this->_logger.log("Window Encapsulation: Window is already initialized, doing nothing...");
        return;
    }
    InitWindow(this->_dimensions.x, this->_dimensions.y, this->_title.c_str());
    this->_windowOpen = true;
}

void Window::init(Vector2 dimensions, std::string title)
{
    if (this->_windowOpen) {
        this->_logger.log("Window Encapsulation: Window is already initialized, doing nothing...");
        return;
    }

    this->_dimensions = dimensions;
    this->_title = title;

    InitWindow(this->_dimensions.x, this->_dimensions.y, this->_title.c_str());
    this->_windowOpen = true;
}

void Window::close()
{
    if (!this->checkWindowOpen())
        return;

    CloseWindow();
    this->_windowOpen = false;
}

// Display Methods
void Window::clearWindow(Color color)
{
    if (!this->checkWindowOpen())
        return;
    ClearBackground(color);
}

// Returns true if open, false otherwise
bool Window::checkWindowOpen() const {
    if (!this->_windowOpen) {
        this->_logger.log("Window Encapsulation: No window is open, doing nothing...");
        return false;
    }
    return true;
}

// Setters
void Window::setDimensions(const Vector2 &dimensions)
{
    if (this->_windowOpen)
        this->_logger.log("Window Encapsulation: Window is already open, changes will only apply if restarted");
    this->_dimensions = dimensions;
}

void Window::setTitle(const std::string &title)
{
    if (this->_windowOpen)
        this->_logger.log("Window Encapsulation: Window is already open, changes will only apply if restarted");
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