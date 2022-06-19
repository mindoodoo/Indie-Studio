/*
** EPITECH PROJECT, 2022
** indie_studio
** File description:
** Window
*/

#include "Window.hpp"

// Construction / Destruction
RL::Window::Window(std::string title, Vector2i dimensions, bool initLater)
    : _dimensions(dimensions), _windowOpen(false), _logger(Logger("WindowEncapsulation"))
{
    if (!initLater) {
        InitWindow(this->_dimensions.x, this->_dimensions.y, title.c_str());
        this->_windowOpen = true;
        SetTargetFPS(60);
    }
    this->_camera.setPosition((Vector3f){ 0.0f, 20.0f, 10.0f });  // Camera position
    this->_camera.setTarget((Vector3f){ 0.0f, 0.0f, -1.0f });      // Camera looking at point
    this->_camera.setRotation((Vector3f){ 0.0f, 1.0f, 0.0f });          // Camera up vector (rotation towards target)
    this->_windowFont = LoadFontEx(".RaylibTesting/Assets/Fonts/Game_Of_Squids.ttf", 20, 0, 250);
    this->_headFont = LoadFontEx(".RaylibTesting/Assets/Fonts/Game_Of_Squids.ttf", 100, 0, 250);
    this->_txtFont = LoadFontEx(".RaylibTesting/Assets/Fonts/Game_Of_Squids.ttf", 50, 0, 250);
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
    SetTargetFPS(60);
}

void RL::Window::init(Vector2i dimensions, std::string title)
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
    // std::cout << "Clearing window" << std::endl;
    ClearBackground(WHITE);
}

void RL::Window::queueDrawable(IDrawable *drawable)
{
    RL::DrawableType type = drawable->getType();
    
    if (type == RL::DrawableType::Type3D)
        this->_displayQueue3D.push_back(drawable);
    if (type == RL::DrawableType::Type2D)
        this->_displayQueue2D.push_back(drawable);
}

void RL::Window::removeDrawable(IDrawable *drawable)
{
    RL::DrawableType type = drawable->getType();
    
    if (type == RL::DrawableType::Type3D)
        this->_displayQueue3D.erase(std::remove(this->_displayQueue3D.begin(), this->_displayQueue3D.end(), drawable), this->_displayQueue3D.end());
    if (type == RL::DrawableType::Type2D)
        this->_displayQueue2D.erase(std::remove(this->_displayQueue2D.begin(), this->_displayQueue2D.end(), drawable), this->_displayQueue2D.end());
}

void RL::Window::displayDrawable2D(RL::Drawable2D drawable)
{
    DrawTexture(drawable.getTexture(), drawable.getPosition().x, drawable.getPosition().y, drawable.getTint());
}

void RL::Window::clearDrawables()
{
    this->_displayQueue2D.clear();
    this->_displayQueue3D.clear();
}

void RL::Window::displayDrawables(Map map, std::string text, int textX, int textY)
{
    BeginDrawing();
    if (!this->_displayQueue3D.empty()) {
        BeginMode3D(this->_camera.getCamera());
        map.draw_map();
        for (auto drawable: this->_displayQueue3D) {
            if (!drawable->isHidden())
                drawable->draw();
        }
        EndMode3D();
    }
    for (auto drawable: this->_displayQueue2D)
        drawable->draw();
    draw_text(text, BLACK, textX, textY, _txtFont, 40);
    EndDrawing();
}

void RL::Window::draw_text(std::string text, Color color, int x, int y, Font font, float size)
{
    //DrawText(text.c_str(), x, y, 20, color);

    //use this function when we get font handled
    DrawTextEx(font, text.c_str(), Vector2 {float(x), float(y)}, size, 2, color);
}

// Returns true if open, false otherwise
bool RL::Window::checkWindowOpen() const
{
    // Implement shouldWindowClose method from raylib ?
    if (!this->_windowOpen) {
        this->_logger.log("Window Encapsulation: No window is open, doing nothing...");
        return false;
    }
    return true;
}

// Setters
void RL::Window::setDimensions(const Vector2i &dimensions)
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
const RL::Vector2i &RL::Window::getDimensions() const
{
    return this->_dimensions;
}

const std::string &RL::Window::getTitle() const
{
    return this->_title;
}

bool RL::Window::isWindowOpen()
{
    if (WindowShouldClose())
        this->_windowOpen = false;
    return this->_windowOpen;
}


const std::vector<RL::IDrawable*> RL::Window::get3Dqueue() const
{
    return this->_displayQueue3D;
}

void RL::Window::removeElemtfrom3Dqueue(int index) {
    _displayQueue3D.erase(_displayQueue3D.begin() + index);
}

Font RL::Window::getFont()
{
    return this->_windowFont;
}

Font RL::Window::getHeadFont()
{
    return this->_headFont;
}

Font RL::Window::getTxtFont()
{
    return this->_txtFont;
}

