/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** Button
*/

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include <raylib.h>
#include <string>
#include <sys/stat.h>
#include <stdexcept>
#include <memory>
#include "RaylibTypeEncaps.hpp"
#include <vector>
#include "Drawable2D.hpp"
#include "Window.hpp"

namespace RL {
    class Button {
        public:
            Button(std::string txt, RL::Vector3f pos, std::string src1, std::string src2, std::string src3, int txtSize, std::shared_ptr<RL::Window> Window);
            ~Button();

            Rectangle getBtnBounds();
            void setBtnBounds(Rectangle newBounds);

            int getBtnState();
            void setBtnState(int newState);

            bool getBtnAction();
            void setBtnAction(bool newAction);

            RL::Vector3f getBtnPos();
            void setBtnPos(RL::Vector3f newPos);

            int getHeight();
            void setHeight(int newHeight);

            int getWidth();
            void setWidth(int newWidth);

            std::string getBtnTxt();
            void setBtnTxt(std::string newStr);

            int getTxtSize();
            void setTxtSize(int size);

            void drawButton();
            void btnAction();

            void setBtnSelected(bool selected);
            bool getBtnSelected();

        private:
            std::shared_ptr<RL::Window> _window;
            std::string _txt;
            Rectangle _btnBounds;
            int _btnState;
            bool _btnAction;
            RL::Vector3f _btnPos;
            int _height;
            int _width;
            int _txtSize;
            std::vector<RL::Drawable2D> _btnTxture;
            bool _selected;
    };
}

#endif /* !BUTTON_HPP_ */
