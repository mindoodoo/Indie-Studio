/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** Button
*/

#include "Button.hpp"

RL::Button::Button(std::string txt, RL::Vector3f pos, std::string src1, std::string src2, std::string src3, int txtSize, std::shared_ptr<RL::Window> Window) : _window(Window)
{
    _btnTxture.push_back(RL::Drawable2D(src1));
    _btnTxture.push_back(RL::Drawable2D(src2));
    _btnTxture.push_back(RL::Drawable2D(src3));
    for (int i = 0; i < _btnTxture.size(); i++)
        _btnTxture[i].setPosition(pos.x, pos.y, pos.z);
    _height = _btnTxture[0].getTexture().height;
    _width = _btnTxture[0].getTexture().width;
    _btnState = 0;
    _btnAction = false;
    _btnPos = pos;
    _btnBounds = { pos.x, pos.y, (float)_width, (float)_height};
    _txt = txt;
    _txtSize = txtSize;
    _selected = false;
}

RL::Button::~Button()
{
}

Rectangle RL::Button::getBtnBounds()
{
    return _btnBounds;
}

void RL::Button::setBtnBounds(Rectangle newBounds)
{
    _btnBounds = newBounds;
}

int RL::Button::getBtnState()
{
    return _btnState;
}

void RL::Button::setBtnState(int newState)
{
    _btnState = newState;
}

bool RL::Button::getBtnAction()
{
    return _btnAction;
}

void RL::Button::setBtnAction(bool newAction)
{
    _btnAction = newAction;
}

RL::Vector3f RL::Button::getBtnPos()
{
    return _btnPos;
}

void RL::Button::setBtnPos(RL::Vector3f newPos)
{
    _btnPos = newPos;
}

int RL::Button::getHeight()
{
    return _height;
}

void RL::Button::setHeight(int newHeight)
{
    _height = newHeight;
}

int RL::Button::getWidth()
{
    return _height;
}

void RL::Button::setWidth(int newWidth)
{
    _width = newWidth;
}

std::string RL::Button::getBtnTxt()
{
    return _txt;
}

void RL::Button::setBtnTxt(std::string newStr)
{
    _txt = newStr;
}

int RL::Button::getTxtSize()
{
    return _txtSize;
}

void RL::Button::setTxtSize(int size)
{
    _txtSize = size;
}

void RL::Button::drawButton()
{
    if (_btnState == 0) {
        _btnTxture[0].draw();
        _window->draw_text(_txt, BLACK, _btnPos.x + (_width / 2 - MeasureTextEx(_window->getTxtFont() , _txt.c_str(), _txtSize, 0).x / 2), _btnPos.y + (_height / 2 - MeasureTextEx(_window->getTxtFont(), _txt.c_str(), _txtSize, 0).y / 2), _window->getTxtFont(), _txtSize);
    } else if (_btnState == 1) {
        _btnTxture[1].draw();
        _window->draw_text(_txt, BLACK, _btnPos.x + (_width / 2 - MeasureTextEx(_window->getTxtFont(), _txt.c_str(), _txtSize, 0).x / 2), _btnPos.y + (_height / 2 - MeasureTextEx(_window->getTxtFont(), _txt.c_str(), _txtSize, 0).y / 2), _window->getTxtFont(), _txtSize);
    } else if (_btnState == 2) {
        _btnTxture[2].draw();
        _window->draw_text(_txt, BLACK, _btnPos.x + (_width / 2 - MeasureTextEx(_window->getTxtFont(), _txt.c_str(), _txtSize, 0).x / 2), _btnPos.y + (_height / 2 - MeasureTextEx(_window->getTxtFont(), _txt.c_str(), _txtSize, 0).y / 2), _window->getTxtFont(), _txtSize);
    }
}

void RL::Button::btnAction()
{
    if (_btnAction == false)
        _btnAction = true;
    else
        _btnAction = false;
}

void RL::Button::setBtnSelected(bool selected)
{
    _selected = selected;
}

bool RL::Button::getBtnSelected()
{
    return _selected;
}
