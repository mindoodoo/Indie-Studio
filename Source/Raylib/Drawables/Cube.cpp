/*
** EPITECH PROJECT, 2022
** Cube.cpp
** File description:
** .
*/

#include "Cube.hpp"

RL::Cube::Cube(Vector3f size, Vector3f position, Color color)
{
    this->_color = color;
    this->_size = size;
    this->_position = position;
    this->_type = DrawableType::Type3D;
}

void RL::Cube::draw()
{
    float x = this->_size.x * this->_scale;
    float y = this->_size.y * this->_scale;
    float z = this->_size.z * this->_scale;
    
    if (this->_textureSet)
        DrawCubeTexture(this->_texture, this->_position, x, y, z, this->_color);
    else
        DrawCube(this->_position, x, y, z, this->_color);
}

void RL::Cube::loadTexture(std::string path)
{
    struct stat sb;

    if (stat(path.c_str(), &sb) == -1)
        throw std::invalid_argument("Asset path is invalid");
    if (S_ISDIR(sb.st_mode))
        throw std::invalid_argument("Asset path is a directory");

    this->_image = LoadImage(path.c_str());
    this->_texture = LoadTextureFromImage(this->_image);
    this->_textureSet = true;
}

void RL::Cube::resetTexture()
{
    this->_textureSet = false;
}

void RL::Cube::setColor(Color color)
{
    this->_color = color;
}

void RL::Cube::setPosition(Vector3f position)
{
    this->_position = position;
}

void RL::Cube::setScale(float scale)
{
    this->_scale = scale;
}

void RL::Cube::setRotation(Vector3f rotation)
{
    this->_rotation = rotation;
}

void RL::Cube::setSize(Vector3f size)
{
    this->_size = size;
}

RL::DrawableType RL::Cube::getType() const
{
    return this->_type;
}

RL::Cube::~Cube()
{
}
