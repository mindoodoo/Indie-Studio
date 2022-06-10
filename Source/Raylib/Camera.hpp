/*
** EPITECH PROJECT, 2022
** Camera.cpp
** File description:
** .
*/

#pragma once

#include <raylib.h>

#include "RaylibTypeEncaps.hpp"

namespace RL {
    enum CameraType {
        CAMERA_3D,
        CAMERA_2D
    };
    
    // Note: Rotation a bit odd, not really working
    class Camera {
        public:
            Camera(CameraType type = CameraType::CAMERA_3D);
            ~Camera();

            // Getters
            Vector3f getPosition() const;
            Vector3f getTarget() const;
            Vector3f getRotation() const;
            Camera3D getCamera() const;

            // Setters
            void setPosition(Vector3f position);
            void setTarget(Vector3f target);
            void setRotation(Vector3f rotation);


        private:
            Camera3D _cam;
            CameraType _type;

            Vector3f _position = {0, 0, 0};
            Vector3f _target = {0, 0, 0};
            Vector3f _rotation = {0, 0, 0};
            
            float _fov = 45.0f;
            int _projection = CAMERA_PERSPECTIVE;
    };
}

