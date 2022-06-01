/*
** EPITECH PROJECT, 2022
** Drawable2D.cpp
** File description:
** .
*/

#include "Drawable2D.hpp"

RL::Drawable2D::Drawable2D(std::string assetPath)
{

}

RL::Drawable2D::~Drawable2D()
{

}

void RL::Drawable2D::draw()
{
    
}

void RL::Drawable2D::loadImage(std::string assetPath)
{
    struct stat sb;

    if (stat(assetPath.c_str(), &sb) == -1)
        throw std::invalid_argument("Asset path is invalid");
    if (S_ISDIR(sb.st_mode))
        throw std::invalid_argument("Asset path is a directory");
    this->_img = LoadImage(assetPath.c_str());
    this->_texture = LoadTextureFromImage(this->_img);
    this->_imageLoaded = true;
}

bool RL::Drawable2D::isImageLoaded() const
{
    return this->_imageLoaded;
}
