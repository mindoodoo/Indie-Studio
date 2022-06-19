/*
** EPITECH PROJECT, 2022
** indie_studio
** File description:
** Drawable3D
*/

#include "Drawable3D.hpp"
RL::Drawable3D::Drawable3D(RL::ModelType type, float scale)
{
    this->_modelType = type;
    this->_scale = scale;
    this->up = 0;
    this->_assetLoaded = true;
    this->_currentAnim = 0;
    this->_currentFrame = 0;
    this->_animationLoaded = false;
    this->_rotationAngle = 0.0f;

}

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
        //DrawSphere(this->_position, 0.5f, RED);
    }
    if (this->_modelType == RL::POWER)
        drawPower();  //here we implement the movement and rotation of the poweup and bouncy etc etc and smaller size etc etc
    
    if (this->_modelType == RL::COIN)
        drawCoin();
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
    if (this->_position.y <= 1.11f && this->up == 1) {
        this->_position.y += 0.01f;
        DrawCubeTexture(this->_texture, this->_position, 0.6f, 0.6f, 0.6f, WHITE);
        // std::cout << "Pos y:"<<_position.y << " Pos" << _position.z << std::endl;
        //DrawSphere(this->_position, 0.05f, WHITE);
        if (this->_position.y >= 1.1f)
            this->up = 0;
        }

}

void RL::Drawable3D::drawCoin()
{
    this->_rotationAngle += 3;
    if (this->_rotationAngle >= 360)
        this->_rotationAngle = 0;
    DrawModelEx(this->_model, this->_position, {0, 1, 0}, this->_rotationAngle, (Vector3f) {this->_scale,this->_scale,this->_scale} , WHITE);
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
    // if (this->_modelType != RL::MODEL) {
        this->_img = LoadImage(texturePath.c_str());
        this->_texture = LoadTextureFromImage(this->_img);
    // }
    if (this->_modelType == RL::MODEL || this->_modelType == RL::COIN) {
        this->_model = LoadModel(modelPath.c_str());
        SetMaterialTexture(&this->_model.materials[0], MATERIAL_MAP_DIFFUSE, this->_texture);
        //HERE ADD LOAD ANIMATION, 
        loadAnimation(animationPath);
        // setCurrentAnim(1);
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
    
    //mcguyver fix for bomb laying? if this->_currentFrame > 24 setCurrentAnim(0); and set
    //_bombAnimState to -1 --edit : not needed after all, we just tell the movement system to not go
    // to idle if its in state 2
    //it means that when the animation loop is over we go above the 24 frames, and
    // and automatically it reverts the animation to IDLE (0);

    if (this->_currentFrame > this->_animations[this->_currentAnim].frameCount && this->_currentAnim == 2) {
        setCurrentAnim(0);
    }
    
    UpdateModelAnimation
    (this->_model, this->_animations[this->_currentAnim], this->_currentFrame);
}

void RL::Drawable3D::setCurrentAnim(int anim)
{

    if (this->_currentAnim != anim)
        this->resetAnimSequence();

    if (anim >= this->_animCount) {
        std::cerr << "Animation index invalid" << std::endl;
        return;
    }
    this->_currentAnim = anim;

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
    if (this->_modelType == RL::MODEL || this->_modelType == RL::COIN)
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


float RL::Drawable3D::getScale()
{
    return this->_scale;
}

void RL::Drawable3D::setUpvalue(int newup)
{
    this->up = newup;
}

int RL::Drawable3D::getUpvalue()
{
    return this->up;
}

Model RL::Drawable3D::getModel()
{
    return this->_model;
}

void RL::Drawable3D::setModel(Model model)
{
    this->_model = model;
}

RL::ModelType RL::Drawable3D::getModelType()
{
    return this->_modelType;
}

void RL::Drawable3D::setRotation(float newRotation)
{
    this->_rotationAngle = newRotation;
}

void RL::Drawable3D::setHidden(bool hidden)
{
    _hidden = hidden;
}

bool RL::Drawable3D::isHidden() const
{
    return _hidden;
}

void RL::Drawable3D::setModelAnimation(ModelAnimation* anim)
{
    this->_animations = anim;
}

ModelAnimation *RL::Drawable3D::getModelAnimation()
{
    return this->_animations;
}

void RL::Drawable3D::setLoadedAnimationTrue()
{
    this->_animationLoaded = true;
}

bool RL::Drawable3D::checkIfHidden()
{
    return _hidden;
}