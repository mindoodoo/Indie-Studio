/*
** EPITECH PROJECT, 2022
** indie_studio
** File description:
** Drawable3D
*/

#include "Drawable3D.hpp"

RL::Drawable3D::Drawable3D(std::string texturePath, std::string modelPath, float scale, ModelType type)
{
    this->_type = type;
    this->_scale = scale;
    if (_type == RL::ModelType::WALL || _type == RL::ModelType::CRATE)
        _boxSize = {1.0, 1.0, 1.0};
    if (_type == ModelType::FLOOR)
        _boxSize = {1.0, 0.5, 1.0};

    this->load3DModel(texturePath, modelPath);
}

RL::Drawable3D::~Drawable3D()
{
    //this->unloadAll();
}

void RL::Drawable3D::draw()
{
    //BeginDrawing();
    if (this->_type == RL::WALL)
        DrawCubeTexture(this->_texture, this->_position, 1.0f, 1.0f, 1.0f, WHITE);
    if (this->_type == RL::MODEL)
        DrawModel(this->_model, this->_position, this->_scale, WHITE);
    //EndDrawing();
}

void RL::Drawable3D::load3DModel(std::string texturePath, std::string modelPath)
{
    struct stat sb;

    if (stat(texturePath.c_str(), &sb) == -1)
        throw std::invalid_argument("Asset path is invalid");
    if (S_ISDIR(sb.st_mode))
        throw std::invalid_argument("Asset path is a directory");
    if (this->_imageLoaded)
        this->unloadAll();
    this->_img = LoadImage(texturePath.c_str());
    this->_texture = LoadTextureFromImage(this->_img);
    if (this->_type == RL::MODEL) {
        this->_model = LoadModel(modelPath.c_str());
        SetMaterialTexture(&this->_model.materials[0], MATERIAL_MAP_DIFFUSE, this->_texture);
    }
    this->_imageLoaded = true;
}

void RL::Drawable3D::setBoundingBox()
{
    if (this->_type == RL::MODEL)
        this->_boundingBox = GetModelBoundingBox(this->_model);
    
    //if (this->_type == RL::WALL || this->_type == RL::FLOOR)
        //this->_boundingBox = {(Vector3) {this->_position.x - this->_model., this->_position.y, this->_position.z}}

}

void RL::Drawable3D::unloadAll()
{
    if (!this->_imageLoaded)
        return;
    UnloadImage(this->_img);
    UnloadTexture(this->_texture);
    this->_imageLoaded = false;
}

void RL::Drawable3D::resize(float newScale)
{
    this->_scale = newScale;
}

bool RL::Drawable3D::isImageLoaded() const
{
    return this->_imageLoaded;
}

void RL::Drawable3D::setTint(Color newTint)
{
    this->_tint = newTint;
}

void RL::Drawable3D::setPosition(float x, float y, float z)
{
    this->_position.x = x;
    this->_position.y = y;
    this->_position.z = z;
}

Vector3 RL::Drawable3D::getPosition()
 {
     return this->_position;
 }

 Vector3 RL::Drawable3D::getBoxSize()
 {
     return this->_boxSize;
 }

 Texture2D RL::Drawable3D::getTexture()
 {
     return this->_texture;
 }
