/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** CharacterSelect
*/

#include "CharacterSelect.hpp"

Win::CharacterSelect::CharacterSelect(std::shared_ptr<RL::Window> Window, std::shared_ptr<RL::InputManager> InputManager, std::shared_ptr<RL::SoundManager> SoundManager, std::shared_ptr<RL::SaveManager> SaveManager) : _window(Window), _inputManager(InputManager), _soundManager(SoundManager), _saveManager(SaveManager)
{
    _name = "CharSelect";
    _mousePt = {0,0};
    _bg = new RL::Drawable2D("./menu_source/assets/bg_bomberman.png");
    _win_x = _window->getDimensions().x;
    _win_y = _window->getDimensions().y;
    _bg->resize({_win_x, _win_y});
    _text.push_back("CHARACTER SELECTION");
    _text.push_back("CHAR 1");
    _text.push_back("CHAR 2");
    _text.push_back("CHAR 3");
    _text.push_back("CHAR 4");
    _text.push_back("BACK");
    _text.push_back("QUIT");
    _selected = 0;
    float x = _win_x / 2 - 350;
    float y = _win_y / 4;
    for (int i = 0; i < 6; i++) {
        if (i > 0)
            x = _win_x / 2 + 50;
        if (i % 2 == 0) {
            x = _win_x / 2 - 350;
            y = y + 150;
        }
        RL::Vector3f tmpV = {x, y, 0};
        RL::Button tmp(_text[i+1], tmpV, "./menu_source/assets/btn2smol.png",  "./menu_source/assets/btn2hover.png", "./menu_source/assets/btn2pressed.png", 50, _window);
        _btn.push_back(tmp);
    };
}

Win::CharacterSelect::~CharacterSelect()
{
    if (_bg)
        delete _bg;
}

void Win::CharacterSelect::drawCharSelect()
{
    BeginDrawing();
    _window->clearWindow(WHITE);
    _bg->draw();
    _window->draw_text(_text[0], BLACK, ((_win_x / 2) - MeasureTextEx(_window->getHeadFont(), _text[0].c_str(), _window->getHeadFont().baseSize* 10, 0).x / 2), 50, _window->getHeadFont(), 100);
    for (int i = 0; i < _btn.size(); i++) {
        _btn[i].drawButton();
    }
    EndDrawing();
}

int Win::CharacterSelect::openCharSelect(int mode)
{
    _mousePt = _inputManager->getMousePosition();
    drawCharSelect();
    for (int i = 0; i < _btn.size(); i++) {
        if (_btn[i].getBtnSelected() == false)
            _btn[i].setBtnState(0);
        if (CheckCollisionPointRec(_mousePt, _btn[i].getBtnBounds())) {
            if (_btn[i].getBtnSelected() == false)
                _btn[i].setBtnState(1);
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                if (mode == 1 && _selected == 1) {
                    if (_btn[i].getBtnSelected() == false) {
                        _btn[i].setBtnState(0);
                        _btn[i].setBtnAction(true);
                        _btn[i].setBtnSelected(false);
                    }
                } else {
                    if (_btn[i].getBtnSelected() == false) {
                        _btn[i].setBtnState(2);
                        _btn[i].setBtnAction(true);
                        _btn[i].setBtnSelected(true);
                    } else {
                        _btn[i].setBtnState(0);
                        _btn[i].setBtnAction(true);
                        _btn[i].setBtnSelected(false);
                    }
                }
            }
        }
    }
    if (_btn[0].getBtnAction() == true) {
        _btn[0].setBtnAction(false);
        if (_btn[0].getBtnSelected() == true) {
            _btn[0].setBtnState(2);
            _selected++;
        } else if (_selected > 0)
            _selected--;
        if (mode == 1)
            return 5;
        if (_selected == 2)
            return 5;
    }
    if (_btn[1].getBtnAction() == true) {
        _btn[1].setBtnAction(false);
        if (_btn[1].getBtnSelected() == true) {
            _btn[1].setBtnState(2);
            _selected++;
        } else if (_selected > 0)
            _selected--;
        if (mode == 1)
            return 5;
        if (_selected == 2)
            return 5;
    }
    if (_btn[2].getBtnAction() == true) {
        _btn[2].setBtnAction(false);
        if (_btn[2].getBtnSelected() == true) {
            _btn[2].setBtnState(2);
            _selected++;
        } else if (_selected > 0)
            _selected--;
        if (mode == 1)
            return 5;
        if (_selected == 2)
            return 5;
    }
    if (_btn[3].getBtnAction() == true) {
        _btn[3].setBtnAction(false);
        if (_btn[3].getBtnSelected() == true) {
            _btn[3].setBtnState(2);
            _selected++;
        } else if (_selected > 0)
            _selected--;
        if (mode == 1)
            return 5;
        if (_selected == 2)
            return 5;
    }
    if (_btn[4].getBtnAction() == true) {
        _btn[4].setBtnAction(false);
        _btn[0].setBtnSelected(false);
        _btn[1].setBtnSelected(false);
        _btn[2].setBtnSelected(false);
        _btn[3].setBtnSelected(false);
        _btn[4].setBtnSelected(false);
        _selected = 0;
        return 0;
    }
    if (_btn[5].getBtnAction() == true) {
        _btn[5].setBtnAction(false);
        _btn[5].setBtnSelected(false);
        return 4;
    }
    return mode;
}