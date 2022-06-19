/*
** EPITECH PROJECT, 2022
** indie_studio
** File description:
** Drawable3D
*/

#pragma once

#include "IDrawable.hpp"

#define MODEL_RADIUS = 0.45f

namespace RL {
    enum ModelType {
        WALL,
        CRATE,
        MODEL,
        FLOOR,
        POWER,
        COIN
    };


    // Used to display and manage a 3D Model
    class Drawable3D: public IDrawable {
        public:
            // Model path is a .iqm and texturepath is a .png
            Drawable3D(RL::ModelType type, float scale);
            Drawable3D(std::string texturePath, std::string modelPath, std::string animationPath, RL::ModelType type, float scale=1);
            ~Drawable3D();

            // IDrawable methods
            void draw();
            void drawPower();
            void drawCoin();

            //------------- Image Loading / Manipulation methods -------------//

            // Takes PNG and IQM path as arg and
            // Loads model and applies texture
            void load3DModel(std::string texturePath, std::string modelPath, std::string animationPath);

            void unloadAll(); // Unload texture and model
            void resize(float newScale); // Change scale of model

            // Animation

            // Takes IQM path as arg
            // Loads animations for loaded model
            void loadAnimation(std::string path);

            // Unload animation
            void unloadAnimation();

            // Sets next frame in animation
            void updateModelsAnimation();

            // Resets animation back to first frame
            void resetAnimSequence();

            // Change animations
            // (Animations loaded are an array of animations (each of which has multiple frames))
            // Arg is the index of the animation in the animations array
            // Note: the animations array is loaded from one single .iqm
            void setCurrentAnim(int anim);

            int getCurrentAnim() const;

            // Check if animation is loaded
            bool isAnimLoaded() const;

            bool isAssetLoaded() const; // Check if model and texture are loaded
            void setTint(Color newTint); // Sets tint of model
            void setRotation(float newRotation); // rotation in Clockwise Angle (0.0 to 360.0)

            void setPosition(Vector3f position);
            Vector3f getPosition();

            Texture2D getTexture();
            DrawableType getType() const;
            ModelType getModelType();

            Vector3f getBoxSize();
            void setBoundingBox();
            BoundingBox getBoundingBox();

            float getScale();

            void setUpvalue(int newup);
            int getUpvalue();

            Model getModel();
            void setModel(Model model);

            ModelAnimation *getModelAnimation();
            void setModelAnimation(ModelAnimation *anim);

            void setHidden(bool hidden);
            bool isHidden() const override;
            bool checkIfHidden();

            void setLoadedAnimationTrue();

        protected:
            Vector3f _position = {0, 0, 0};
            Vector3f _boxSize;

            bool _assetLoaded = false;
            Image _img;
            Texture2D _texture;
            Model _model;
            Color _tint = WHITE;
            float _scale;
            ModelType _modelType;
            BoundingBox _boundingBox;
            int up;

            RL::DrawableType _type = Type3D;

            // Animation
            ModelAnimation *_animations;
            int _currentAnim = 0;
            int _currentFrame = 0;
            unsigned int _animCount;
            bool _animationLoaded = false;
            float _rotationAngle = 0.0f;
    };
}