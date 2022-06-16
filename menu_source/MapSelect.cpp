/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** MapSelect
*/

#include "MapSelect.hpp"

Win::MapSelect::MapSelect(std::shared_ptr<RL::Window> Window, std::shared_ptr<RL::InputManager> InputManager, std::shared_ptr<RL::SoundManager> SoundManager) : _window(Window), _inputManager(InputManager), _soundManager(SoundManager)
{
    _mousePt = {0,0};
    _bg = new RL::Drawable2D("./menu_source/assets/bg_bomberman.png");
    _name = "START";
    _win_x = _window->getDimensions().x;
    _win_y = _window->getDimensions().y;
    _bg->resize({_win_x, _win_y});
    _text.push_back("Select Map");
    _text.push_back("BACK");
    _text.push_back("QUIT");
    std::vector<int> num = {1, 2, 3, 4, 5, 6};
    float x = _win_x / 2 - 350;
    float y = _win_y / 10;
    int z = 1;
    for (int i = 0; i < num.size() + 2; i++) {
        if (i > 0)
            x = _win_x / 2 + 50;
        if (i % 2 == 0) {
            x = _win_x / 2 - 350;
            y = y + 150;
        }
        if (i == num.size()) {
            x = _win_x / 2 - 350;
            y = _win_y - 150;
        }
        if (i == num.size() + 1) {
            x = _win_x / 2 + 50;
            y = _win_y - 150;
        }
        RL::Vector3f tmpV = {x, y, 0};
        if (i < num.size()) {
            RL::Button tmp(std::to_string(num[i]), tmpV, "./menu_source/assets/btn2smol.png", "./menu_source/assets/btn2hover.png", "./menu_source/assets/btn2pressed.png", 50, _window);
            _btn.push_back(tmp);
        } else {
            RL::Button tmp(_text[z], tmpV, "./menu_source/assets/btn2smol.png", "./menu_source/assets/btn2hover.png", "./menu_source/assets/btn2pressed.png", 50, _window);
            _btn.push_back(tmp);
            z++;
        }
    }
}

Win::MapSelect::~MapSelect()
{
    if (_bg)
        delete _bg;
}

void Win::MapSelect::drawMapMenu()
{
    BeginDrawing();
    _window->clearWindow(WHITE);
    _bg->draw();
    _window->draw_text(_text[0], BLACK, (_win_x / 2 - MeasureTextEx(_window->getHeadFont(), _text[0].c_str(), _window->getHeadFont().baseSize* 10, 0).x / 2), 50, _window->getHeadFont(), 100);
    for (int i = 0; i < _btn.size(); i++)
        _btn[i].drawButton();
    EndDrawing();
}

int Win::MapSelect::openMapMenu(int prev)
{
    _mousePt = _inputManager->getMousePosition();
    drawMapMenu();
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
        return 6;
         // choose map
    }
    if (_btn[1].getBtnAction() == true) {
        _btn[1].setBtnAction(false);
        return 6;
        // choose map
    }
    if (_btn[_btn.size() - 2].getBtnAction() == true) {
        _btn[_btn.size() - 2].setBtnAction(false);
        return prev;
    }
    if (_btn[_btn.size() - 1].getBtnAction() == true) {
        _btn[_btn.size() - 1].setBtnAction(false);
        return 4;
    }
    return 5;
}