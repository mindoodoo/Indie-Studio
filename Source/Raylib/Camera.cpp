/*
** EPITECH PROJECT, 2022
** Camera.cpp
** File description:
** .
*/

#include "Camera.hpp"

RL::Camera::Camera(RL::CameraType type): _type(type)
{
    if (type == RL::CameraType::CAMERA_3D) {
        this->_cam = {0};
        this->_cam.position = this->_position;
        this->_cam.target = this->_target;
        this->_cam.up = this->_rotation;
        this->_cam.fovy = this->_fov;
        this->_cam.projection = CAMERA_PERSPECTIVE;
    } else {
        // Handle 2D Camera here
    }
}

RL::Camera::~Camera()
{
}

// Setters
void RL::Camera::setPosition(RL::Vector3f position)
{
    this->_position = position;
    this->_cam.position = position;
}

void RL::Camera::setTarget(RL::Vector3f target)
{
    this->_target = target;
    this->_cam.target = target;
}

void RL::Camera::setRotation(RL::Vector3f rotation)
{
    this->_rotation = rotation;
    this->_cam.up = rotation;
}

// Getters
Camera3D RL::Camera::getCamera() const
{
    return this->_cam;
}

RL::Vector3f RL::Camera::getPosition() const
{
    return this->_position;
}

RL::Vector3f RL::Camera::getTarget() const
{
    return this->_target;
}

RL::Vector3f RL::Camera::getRotation() const
{
    return this->_rotation;
}