/*
** EPITECH PROJECT, 2022
** indie
** File description:
** startmenu
*/

#include "StartMenu.hpp"

Win::StartMenu::StartMenu(std::shared_ptr<RL::Window> Window, std::shared_ptr<RL::InputManager> InputManager, std::shared_ptr<RL::SoundManager> SoundManager, std::shared_ptr<RL::SaveManager> SaveManager) : _window(Window), _inputManager(InputManager), _soundManager(SoundManager), _saveManager(SaveManager)
{
    _mousePt = {0,0};
    _bg = new RL::Drawable2D("./menu_source/assets/bg_bomberman.png");
    _intro = new RL::Drawable2D("./menu_source/assets/introScene.png");
    _name = "START";
    _win_x = _window->getDimensions().x;
    _win_y = _window->getDimensions().y;
    _bg->resize({_win_x, _win_y});
    _intro->resize({_win_x, _win_y});
    _text.push_back("BOMBERMAN");
    _text.push_back("1 PLAYER");
    _text.push_back("2 PLAYER");
    _text.push_back("LOAD GAME");
    _text.push_back("SETTINGS");
    _text.push_back("QUIT");
    float x = _win_x / 2 - 350;
    float y = _win_y / 3;
    for (int i = 0; i < 5; i++) {
        if (i > 0)
            x = _win_x / 2 + 50;
        if (i == 2) {
            x = _win_x / 2 - 350;
            y = y + 150;
        }
        if (i == 4) {
            x = _win_x / 2 - 150;
            y = y + 150;
        }
        RL::Vector3f tmpV = {x, y, 0};
        RL::Button tmp(_text[i+1], tmpV, "./menu_source/assets/btn2smol.png", "./menu_source/assets/btn2hover.png", "./menu_source/assets/btn2pressed.png", 50, _window);
        _btn.push_back(tmp);
    }
}

Win::StartMenu::~StartMenu()
{
    if (_bg)
        delete _bg;
    if (_intro)
        delete _intro;
}

void Win::StartMenu::drawMenu()
{
    BeginDrawing();
    _window->clearWindow(WHITE);
    _bg->draw();
    _window->draw_text(_text[0], BLACK, (_win_x / 2 - MeasureTextEx(_window->getHeadFont(), _text[0].c_str(), _window->getHeadFont().baseSize * 10, 0).x / 2), 50, _window->getHeadFont(), 100);
    for (int i = 0; i < _btn.size(); i++)
        _btn[i].drawButton();
    EndDrawing();
}

int Win::StartMenu::openStartMenu()
{
    _mousePt = _inputManager->getMousePosition();
    drawMenu();
    for (int i = 0; i < _btn.size(); i++) {
        _btn[i].setBtnState(0);
        if (CheckCollisionPointRec(_mousePt, _btn[i].getBtnBounds())) {
            _btn[i].setBtnState(1);
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                _btn[i].setBtnState(2);
                _btn[i].setBtnAction(true);
            }
        }
    }
    if (_btn[0].getBtnAction() == true) {
        _btn[0].setBtnAction(false);
        return 1;
    }
    if (_btn[1].getBtnAction() == true) {
        _btn[1].setBtnAction(false);
        return 2;
    }
    if (_btn[2].getBtnAction() == true) {
        _btn[2].setBtnAction(false);
        return 10;
    }
    if (_btn[3].getBtnAction() == true) {
        _btn[3].setBtnAction(false);
        return 3;
    }
    if (_btn[4].getBtnAction() == true) {
        _btn[4].setBtnAction(false);
        return 4;
    }
    return 0;
}

int Win::StartMenu::starIntro()
{
    BeginDrawing();
    _window->clearWindow(WHITE);
    _intro->draw();
    EndDrawing();
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    return 0;
}