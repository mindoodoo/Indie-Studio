/*
** EPITECH PROJECT, 2022
** indie_studio
** File description:
** Drawable3D
*/

#include "Drawable3D.hpp"

RL::Drawable3D::Drawable3D(std::string texturePath, std::string modelPath, std::string animationPath, RL::ModelType type, float scale)
{
    this->_modelType = type;
    this->_scale = scale;
    this->up = 0;
    if (_modelType == RL::ModelType::WALL || _modelType == RL::ModelType::CRATE)
        _boxSize = {1.0, 1.0, 1.0};
    if (_modelType == ModelType::FLOOR)
        _boxSize = {1.0, 0.5, 1.0};

    this->load3DModel(texturePath, modelPath, animationPath);
}

RL::Drawable3D::~Drawable3D()
{
    // this->unloadAll();   
}

void RL::Drawable3D::draw()
{
    //BeginDrawing();
    if (this->_modelType == RL::WALL)
        DrawCubeTexture(this->_texture, this->_position, 1.0f, 1.0f, 1.0f, WHITE);
    if (this->_modelType == RL::MODEL) {
        DrawModelEx(this->_model, this->_position, {0, 1, 0}, this->_rotationAngle, (Vector3f) {this->_scale,this->_scale,this->_scale} , WHITE);
        //DrawModel(this->_model, this->_position, this->_scale, WHITE);
        DrawSphere(this->_position, 0.5f, RED);
    }
    if (this->_modelType == RL::POWER)
        drawPower();  //here we implement the movement and rotation of the poweup and bouncy etc etc and smaller size etc etc
    //EndDrawing();
}

void RL::Drawable3D::drawPower()
{
    if (this->_position.y >= 0.59f && this->up == 0) {
        this->_position.y -= 0.01f;
        DrawCubeTexture(this->_texture, this->_position, 0.6f, 0.6f, 0.6f, WHITE);
        //DrawSphere(this->_position, 0.05f, WHITE);
        if (this->_position.y <= 0.6f)
            this->up = 1;
        }
    if (this->_position.y <= 1.41f && this->up == 1) {
        this->_position.y += 0.01f;
        DrawCubeTexture(this->_texture, this->_position, 0.6f, 0.6f, 0.6f, WHITE);
        //DrawSphere(this->_position, 0.05f, WHITE);
        if (this->_position.y >= 1.4f)
            this->up = 0;
        }

}

void RL::Drawable3D::load3DModel(std::string texturePath, std::string modelPath, std::string animationPath)
{
    struct stat sb;

    if (stat(texturePath.c_str(), &sb) == -1)
        throw std::invalid_argument("Asset path is invalid");
    if (S_ISDIR(sb.st_mode))
        throw std::invalid_argument("Asset path is a directory");
    if (this->_assetLoaded)
        this->unloadAll();
    if (this->_modelType != RL::MODEL) {
        this->_img = LoadImage(texturePath.c_str());
        this->_texture = LoadTextureFromImage(this->_img);
    }
    if (this->_modelType == RL::MODEL) {
        this->_model = LoadModel(modelPath.c_str());
        SetMaterialTexture(&this->_model.materials[0], MATERIAL_MAP_DIFFUSE, this->_texture);
        //HERE ADD LOAD ANIMATION, 
        loadAnimation(animationPath);
    }
    this->_assetLoaded = true;
    setBoundingBox();
}

//
// ANIMATION
//

void RL::Drawable3D::loadAnimation(std::string path)
{
    if (path == "")
        return;
    struct stat sb;

    if (stat(path.c_str(), &sb) == -1)
        throw std::invalid_argument("Asset path is invalid");
    if (S_ISDIR(sb.st_mode))
        throw std::invalid_argument("Asset path is a directory");

    if (_animationLoaded)
        this->unloadAnimation();
    this->_animations = LoadModelAnimations(path.c_str(), &this->_animCount);
    this->_animationLoaded = true;
}

void RL::Drawable3D::unloadAnimation()
{
    for (unsigned int i = 0; i < this->_animCount; i++)
        UnloadModelAnimation(this->_animations[i]);
    RL_FREE(this->_animations);
    this->_animationLoaded = false;
}

void RL::Drawable3D::updateModelsAnimation()
{
    if (!this->_animationLoaded)
        return;

    this->_currentFrame++;
    UpdateModelAnimation
    (this->_model, this->_animations[this->_currentAnim], this->_currentFrame);
}

void RL::Drawable3D::setCurrentAnim(int anim)
{
    this->_currentAnim;

    if (anim >= this->_animCount) {
        std::cerr << "Animation index invalid" << std::endl;
        return;
    }

    this->resetAnimSequence();
}

void RL::Drawable3D::resetAnimSequence()
{
    this->_currentFrame = 0;
}

int RL::Drawable3D::getCurrentAnim() const
{
    return this->_currentAnim;
}

void RL::Drawable3D::setBoundingBox()
{
    if (this->_modelType == RL::MODEL)
        this->_boundingBox.max.x = this->_position.x - 0.5f;
        this->_boundingBox.max.y = this->_position.y - 0.5f;
        this->_boundingBox.max.z = this->_position.z - 0.5f;
        this->_boundingBox.min.x = this->_position.x + 0.5f;
        this->_boundingBox.min.y = this->_position.y + 0.5f;
        this->_boundingBox.min.z = this->_position.z + 0.5f;

    
    if (this->_modelType == RL::WALL || this->_modelType == RL::FLOOR)
        this->_boundingBox = {(Vector3f) {this->_position.x - (this->_boxSize.x ) / 2,
                                         this->_position.y - (this->_boxSize.y ) / 2,
                                         this->_position.z - (this->_boxSize.z ) / 2} ,
                              (Vector3f) {this->_position.x + (this->_boxSize.x ) / 2,
                                         this->_position.y + (this->_boxSize.y ) / 2,
                                         this->_position.z + (this->_boxSize.z ) / 2}
                                         };
}

BoundingBox RL::Drawable3D::getBoundingBox()
{
    return this->_boundingBox;
}

void RL::Drawable3D::unloadAll()
{
    if (!this->_assetLoaded)
        return;
    UnloadImage(this->_img);
    UnloadTexture(this->_texture);
    this->_assetLoaded = false;
}

void RL::Drawable3D::resize(float newScale)
{
    this->_scale = newScale;
}

bool RL::Drawable3D::isAssetLoaded() const
{
    return this->_assetLoaded;
}

void RL::Drawable3D::setTint(Color newTint)
{
    this->_tint = newTint;
}

void RL::Drawable3D::setPosition(Vector3f position)
{
    this->_position = position;
    
    setBoundingBox();
}

RL::Vector3f RL::Drawable3D::getPosition()
{
    return this->_position;
}

RL::Vector3f RL::Drawable3D::getBoxSize()
{
    return this->_boxSize;
}

Texture2D RL::Drawable3D::getTexture()
{
    return this->_texture;
}

RL::DrawableType RL::Drawable3D::getType() const
{
    return this->_type;
}

RL::ModelType RL::Drawable3D::getModelType()
{
    return this->_modelType;
}

void RL::Drawable3D::setRotation(float newRotation)
{
    this->_rotationAngle = newRotation;
}


