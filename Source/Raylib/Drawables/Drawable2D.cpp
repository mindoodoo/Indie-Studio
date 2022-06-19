/*
** EPITECH PROJECT, 2022
** Drawable2D.cpp
** File description:
** .
*/

#include "Drawable2D.hpp"

RL::Drawable2D::Drawable2D(std::string assetPath)
{
    this->loadImage(assetPath);
}

RL::Drawable2D::Drawable2D(Texture2D texture, int x, int y)
{
    this->_texture = texture;
    setPosition(x, y, 0);
}

RL::Drawable2D::~Drawable2D()
{
    //this->unloadAll();
}

void RL::Drawable2D::draw()
{
    DrawTexture(this->_texture, this->_position.x, this->_position.y, this->_tint);
}

void RL::Drawable2D::loadImage(std::string assetPath)
{
    struct stat sb;

    if (stat(assetPath.c_str(), &sb) == -1)
        throw std::invalid_argument("Asset path is invalid");
    if (S_ISDIR(sb.st_mode))
        throw std::invalid_argument("Asset path is a directory");
    if (this->_imageLoaded)
        this->unloadAll();
    this->_img = LoadImage(assetPath.c_str());
    this->_texture = LoadTextureFromImage(this->_img);
    this->_imageLoaded = true;
}

void RL::Drawable2D::unloadAll()
{
    if (!this->_imageLoaded)
        return;
    UnloadImage(this->_img);
    UnloadTexture(this->_texture);
    this->_imageLoaded = false;
}

void RL::Drawable2D::resize(Vector2i newSize)
{
    if (!this->_imageLoaded)
        return;
    ImageResize(&this->_img, newSize.x, newSize.y);
    UnloadTexture(this->_texture);
    this->_texture = LoadTextureFromImage(this->_img);
}

bool RL::Drawable2D::isImageLoaded() const
{
    return this->_imageLoaded;
}

void RL::Drawable2D::setTint(Color newTint)
{
    this->_tint = newTint;
}

void RL::Drawable2D::setPosition(float x, float y, float z)
{
    this->_position.x = x;
    this->_position.y = y;
    this->_position.z = z;
}

RL::Vector3f RL::Drawable2D::getPosition()
 {
     return this->_position;
 }

Texture2D RL::Drawable2D::getTexture()
{
    return this->_texture;
}

RL::DrawableType RL::Drawable2D::getType() const
{
    return this->_type;
}

bool RL::Drawable2D::isHidden() const
{
    return _hidden;
}

Color RL::Drawable2D::getTint()
{
    return _tint;
}
