/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** Settings
*/

#include "Settings.hpp"

Win::Settings::Settings(std::shared_ptr<RL::Window> Window, std::shared_ptr<RL::InputManager> InputManager, std::shared_ptr<RL::SoundManager> SoundManager, std::shared_ptr<RL::SaveManager> SaveManager) : _window(Window), _inputManager(InputManager), _soundManager(SoundManager), _saveManager(SaveManager)
{
    _mousePt = {0,0};
    _bg = new RL::Drawable2D("./menu_source/assets/bg_bomberman.png");
    _name = "SETTINGS";
    _win_x = _window->getDimensions().x;
    _win_y = _window->getDimensions().y;
    _bg->resize({_win_x, _win_y});
    _text.push_back("SETTINGS");
    _text.push_back("EFFECT VOLUME");
    _text.push_back("MUSIC VOLUME");
    _text.push_back("MUTE");
    _text.push_back("-");
    _text.push_back("+");
    _text.push_back("-");
    _text.push_back("+");
    _text.push_back("BACK");
    _selected = 0;
    float x = _win_x / 2 - 350;
    float y = _win_y / 3;
    for (int i = 0; i < 6; i++) {
        if (i == 0) {
            x = _win_x / 2 - 150;
            y = _win_y / 4;
        } else if (i == 5) {
            x = _win_x / 2 - 150;
            y = _win_y - 150;
        } else if (i % 2 == 0) {
            x = _win_x / 2 + 50;
        } else {
            x = x = _win_x / 2 - 350;
            y = y + 160;
        }
        RL::Vector3f tmpV = {x, y, 0};
        RL::Button tmp(_text[i+3], tmpV, "./menu_source/assets/btn2smol.png",  "./menu_source/assets/btn2hover.png", "./menu_source/assets/btn2pressed.png", 50, _window);
        _btn.push_back(tmp);
    };
}

Win::Settings::~Settings()
{
    if (_bg)
        delete _bg;
}

void Win::Settings::drawSettings()
{
    BeginDrawing();
    _window->clearWindow(WHITE);
    _bg->draw();
    _window->draw_text(_text[0], BLACK, (_win_x / 2 - MeasureTextEx(_window->getHeadFont(), _text[0].c_str(), _window->getHeadFont().baseSize* 10, 0).x / 2), 50, _window->getHeadFont(), 100);
    _window->draw_text(_text[1], GRAY, (_win_x / 2 - MeasureTextEx(_window->getTxtFont(), _text[1].c_str(), _window->getTxtFont().baseSize*5, 0).x / 2), _win_y / 4 + 112, _window->getTxtFont(), 50);
    _window->draw_text(_text[2], GRAY, (_win_x / 2 - MeasureTextEx(_window->getTxtFont(), _text[2].c_str(), _window->getTxtFont().baseSize*5, 0).x / 2), _win_y / 4 + 272, _window->getTxtFont(), 50);
    for (int i = 0; i < _btn.size(); i++)
        _btn[i].drawButton();
    EndDrawing();
}

int Win::Settings::openSettings(int prev)
{
    _mousePt = _inputManager->getMousePosition();
    drawSettings();
    for (int i = 0; i < _btn.size(); i++) {
        if (_btn[i].getBtnSelected() == false || i != 0)
            _btn[i].setBtnState(0);
        if (CheckCollisionPointRec(_mousePt, _btn[i].getBtnBounds())) {
            if (_btn[i].getBtnSelected() == false || i != 0)
                _btn[i].setBtnState(1);
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                if (i == 0) {
                    if (_btn[i].getBtnSelected() == false) {
                        _selected++;
                        _btn[i].setBtnState(2);
                        _btn[i].setBtnAction(true);
                        _btn[i].setBtnSelected(true);
                    } else {
                        _selected--;
                        _btn[i].setBtnState(2);
                        _btn[i].setBtnAction(true);
                        _btn[i].setBtnSelected(false);
                    }
                } else {
                    _btn[i].setBtnState(2);
                    _btn[i].setBtnAction(true);
                }
            }
        }
        //_soundManager->updateMusicStream();
    }
    if (_btn[0].getBtnAction() == true) {
        _btn[0].setBtnAction(false);
        _soundManager->muteGame();
        //mute game
    }
    if (_btn[1].getBtnAction() == true) {
        _btn[1].setBtnAction(false);
        _soundManager->decreaseSoundEffectVolume();
        _soundManager->playSpecificSoundFx("Item1");
    }
    if (_btn[2].getBtnAction() == true) {
        _btn[2].setBtnAction(false);
        _soundManager->increaseSoundEffectVolume();
        _soundManager->playSpecificSoundFx("Item1");
    }
    if (_btn[3].getBtnAction() == true) {
        _btn[3].setBtnAction(false);
        _soundManager->decreaseMusicVolume();
        //_soundManager->playSpecificMusic("Explosion1");
    }
    if (_btn[4].getBtnAction() == true) {
        _btn[4].setBtnAction(false);
        _soundManager->increaseMusicVolume();
        //_soundManager->playSpecificMusic("Explosion1");

    }
    if (_btn[5].getBtnAction() == true) {
        _btn[5].setBtnAction(false);
        return prev;
    }
    return 3;
}