/*
** EPITECH PROJECT, 2022
** indie_studio
** File description:
** Window
*/

#include "Window.hpp"

// Construction / Destruction
RL::Window::Window(std::string title, Vector2 dimensions, bool initLater)
    : _dimensions(dimensions), _windowOpen(false), _logger(Logger("WindowEncapsulation"))
{
    if (!initLater) {
        InitWindow(this->_dimensions.x, this->_dimensions.y, title.c_str());
        this->_windowOpen = true;
    }
    this->_camera = {0};
    this->_camera.position = (Vector3){ 0.0f, 21.0f, 4.0f };  // Camera position
    this->_camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    this->_camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    this->_camera.fovy = 45.0f;                                // Camera field-of-view Y
    this->_camera.projection = CAMERA_PERSPECTIVE;

}

RL::Window::~Window()
{
    //CloseWindow();
}

// Method to init window if not init on construction
void RL::Window::init()
{
    if (this->_windowOpen) {
        this->_logger.log("Window Encapsulation: Window is already initialized, doing nothing...");
        return;
    }
    InitWindow(this->_dimensions.x, this->_dimensions.y, this->_title.c_str());
    this->_windowOpen = true;
}

void RL::Window::init(Vector2 dimensions, std::string title)
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

void RL::Window::close()
{
    if (!this->checkWindowOpen())
        return;

    CloseWindow();
    this->_windowOpen = false;
}

// Display Methods
void RL::Window::clearWindow(Color color)
{
    if (!this->checkWindowOpen())
        return;
    ClearBackground(color);
}

// Returns true if open, false otherwise
bool RL::Window::checkWindowOpen() const
{
    // Implement shouldWindowClose method from raylib ?
    if (!this->_windowOpen) {
        this->_logger.log("Window Encapsulation: No window is open, doing nothing...");
        return false;
    }
    if (WindowShouldClose())
        return false;
    return true;
}

// Setters
void RL::Window::setDimensions(const Vector2 &dimensions)
{
    if (this->_windowOpen)
        this->_logger.log("Window Encapsulation: Window is already open, changes will only apply if restarted");
    this->_dimensions = dimensions;
}

void RL::Window::setTitle(const std::string &title)
{
    if (this->_windowOpen)
        this->_logger.log("Window Encapsulation: Window is already open, changes will only apply if restarted");
    this->_title = title;
}

// Getters
const Vector2 &RL::Window::getDimensions() const
{
    return this->_dimensions;
}

const std::string &RL::Window::getTitle() const
{
    return this->_title;
}

bool RL::Window::isWindowOpen()
{
    this->_windowOpen = this->checkWindowOpen();

    return this->_windowOpen;
}

const Camera &RL::Window::getCamera() const
{
    return this->_camera;
}