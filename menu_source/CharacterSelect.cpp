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
    _text.push_back("CONFIRM");
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
    // for (int i = 0; i < 4; i++) {
    //     _playerChoice[i].CPU = true;
    //     _playerChoice[i].playerOrder = 0;
    // }
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

PlayerChoice Win::CharacterSelect::fillOutPlayerChoice(std::size_t Character, bool CPU, std::size_t playerOrder)
{
    PlayerChoice newPlayer;
    newPlayer.Character = Character;
    newPlayer.CPU = CPU;
    newPlayer.playerOrder = playerOrder;

    return newPlayer;    
}

void Win::CharacterSelect::clearCharSelected()
{
    if (_playerChoice.size() != 0) {
        _playerChoice.clear();
    }
}

void Win::CharacterSelect::buttonStateUpdate(std::size_t index, int mode)
{
    if (_btn[index].getBtnAction() == true) {
        _btn[index].setBtnAction(false);
        if (_btn[index].getBtnSelected() == true && mode == 2) {
            _btn[index].setBtnState(2);
            if (_playerChoice.empty())
                _playerChoice.push_back(fillOutPlayerChoice(index, false, 1));
            else if (!_playerChoice.empty() && (_playerChoice[0].playerOrder == 2 ))
                _playerChoice.push_back(fillOutPlayerChoice(index, false, 1));
            else 
                _playerChoice.push_back(fillOutPlayerChoice(index, false, 2));
        }
        else if (_btn[index].getBtnSelected() == true && mode == 1) {
            _btn[index].setBtnState(2);
            if (_playerChoice.empty())
                _playerChoice.push_back(fillOutPlayerChoice(index, false, 1));
        }
        
    }
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
                if (i == 4)
                    return 0;
                if (i == 5 && mode == 1 && _selected == 1)
                    return 5;
                else if (i == 5 && mode == 2 && _selected == 2)
                    return 5;
                if (mode == 1 ) {
                    if (_btn[i].getBtnSelected() == false && _selected < 1) {
                        _selected++;
                        _btn[i].setBtnState(2);
                        _btn[i].setBtnAction(true);
                        _btn[i].setBtnSelected(true);
                    }
                    else {
                        if (_btn[i].getBtnSelected() == false && _selected == 1)
                            continue;
                        _selected--;
                        _btn[i].setBtnState(2);
                        _btn[i].setBtnAction(true);
                        _btn[i].setBtnSelected(false);
                        _playerChoice.pop_back();
                    }
                } else {
                    if (_btn[i].getBtnSelected() == false && _selected < 2) {
                        _selected++;
                        _btn[i].setBtnState(2);
                        _btn[i].setBtnAction(true);
                        _btn[i].setBtnSelected(true);
                    } else {
                        if (_btn[i].getBtnSelected() == false && _selected == 2)
                            continue;
                        _selected--;
                        _btn[i].setBtnState(0);
                        _btn[i].setBtnAction(true);
                        _btn[i].setBtnSelected(false);
                        for (int j = 0; j < _playerChoice.size(); j++) {
                            if (_playerChoice[j].Character == i)
                                _playerChoice.erase(_playerChoice.begin() + j);
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < 4; i++)
        buttonStateUpdate(i, mode);
    // if (_btn[0].getBtnAction() == true) {
    //     _btn[0].setBtnAction(false);
    //     if (_btn[0].getBtnSelected() == true) {
    //         _btn[0].setBtnState(2);

    //         if (_playerChoice.empty())
    //             _playerChoice.push_back(fill_out_playerChoice(1, false, 1));
    //         else if (!_playerChoice.empty() && (_playerChoice[0].playerOrder == 2 ))
    //             _playerChoice.push_back(fill_out_playerChoice(1, false, 1));
    //         else 
    //             _playerChoice.push_back(fill_out_playerChoice(1, false, 2));
    //     }
    // }
    // if (_btn[1].getBtnAction() == true) {
    //     _btn[1].setBtnAction(false);
    //     if (_btn[1].getBtnSelected() == true) 
    //         _btn[1].setBtnState(2);
    // }
    // if (_btn[2].getBtnAction() == true) {
    //     _btn[2].setBtnAction(false);
    //     if (_btn[2].getBtnSelected() == true) 
    //         _btn[2].setBtnState(2);
    // }
    // if (_btn[3].getBtnAction() == true) {
    //     _btn[3].setBtnAction(false);
    //     if (_btn[3].getBtnSelected() == true) 
    //         _btn[3].setBtnState(2);
    // }
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
        if ((_selected == 2 && mode == 2) || mode == 1)
            return 5;
    }
    return mode;
}