/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** EndMenu
*/

#include "EndMenu.hpp"

Win::EndMenu::EndMenu(std::shared_ptr<RL::Window> Window, std::shared_ptr<RL::InputManager> InputManager, std::shared_ptr<RL::SoundManager> SoundManager) : _window(Window), _inputManager(InputManager), _soundManager(SoundManager)
{
    _name = "START";
    _mousePt = {0,0};
    _bg = new RL::Drawable2D("./menu_source/assets/bg_bomberman.png");
    _win_x = _window->getDimensions().x;
    _win_y = _window->getDimensions().y;
    _bg->resize({_win_x, _win_y});
    _text.push_back("GAME OVER");
    _text.push_back("PLAYER 1 WINS");
    _text.push_back("PLAYER 2 WINS");
    _text.push_back("CPU WINS");
    _text.push_back("MAIN MENU");
    _text.push_back("QUIT");
    _win = 0;
    float x = _win_x / 2 - 350;
    float y = _win_y / 2;
    for (int i = 0; i < 2; i++) {
        if (i > 0)
            x = _win_x / 2 + 50;
        // if (i == 2) {
        //     x = _win_x / 2 - 350;
        //     y = y + 150;
        // }
        RL::Vector3f tmpV = {x, y, 0};
        RL::Button tmp(_text[i+4], tmpV, "./menu_source/assets/btn2smol.png", "./menu_source/assets/btn2hover.png", "./menu_source/assets/btn2pressed.png", 50, _window);
        _btn.push_back(tmp);
    }
}

Win::EndMenu::~EndMenu()
{
    if (_bg)
        delete _bg;
}

void Win::EndMenu::drawEndMenu()
{
    BeginDrawing();
    _window->clearWindow(WHITE);
    _bg->draw();
    _window->draw_text(_text[0], BLACK, ((_win_x / 2) - MeasureTextEx(_window->getHeadFont(), _text[0].c_str(), _window->getHeadFont().baseSize* 10, 0).x / 2), 50, _window->getHeadFont(), 100);
     if (_win == 1)
        _window->draw_text(_text[1], BLACK,  ((_win_x / 2) - MeasureTextEx(_window->getHeadFont(), _text[1].c_str(), _window->getHeadFont().baseSize* 10, 0).x / 2), 200, _window->getHeadFont(), 100);
    if (_win == 2)
        _window->draw_text(_text[2], BLACK,  ((_win_x / 2) - MeasureTextEx(_window->getHeadFont(), _text[2].c_str(), _window->getHeadFont().baseSize* 10, 0).x / 2), 200, _window->getHeadFont(), 100);
    if (_win == 3)
        _window->draw_text(_text[3], BLACK,  ((_win_x / 2) - MeasureTextEx(_window->getHeadFont(), _text[3].c_str(), _window->getHeadFont().baseSize* 10, 0).x / 2), 200, _window->getHeadFont(), 100);
    for (int i = 0; i < _btn.size(); i++) {
        _btn[i].drawButton();
    }
    EndDrawing();
}

int Win::EndMenu::openEndMenu()
{
    _mousePt = _inputManager->getMousePosition();
    drawEndMenu();
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
        return 0;
    }
    if (_btn[1].getBtnAction() == true) {
        _btn[1].setBtnAction(false);
        return 4;
    }
    return 8;
}