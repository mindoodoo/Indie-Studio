/*
** EPITECH PROJECT, 2022
** .
** File description:
** .
*/
#include "Bomberman.hpp"

bool Bomberman::createExplosion(Pos pos, Skillset skills, EntityID bombOwner)
{
    EntityID id = _em->CreateNewEntity();
    _em->Assign<Pos>(id, pos);
    //BOMBOWNER == EXPLOSIONOWNER
    _em->Assign<BombOwner>(id, {bombOwner});
    _em->Assign<CollisionObjectType>(id, CollisionObjectType{EXPLOSION});
    Timer timer = Timer();
    timer.startTimer();
    _em->Assign<Timer>(id, timer);
    float scale = 2;
    std::string explotex = "./RaylibTesting/Assets/Explosion/textures/fire3lambert1_baseColor.png";
    std::string explomod = "./RaylibTesting/Assets/Explosion/textures/fire.obj";
    RL::Drawable3D *Explosion = new RL::Drawable3D(explotex, explomod, "", RL::MODEL, scale);
    Explosion->setPosition((RL::Vector3f){
            translateFigureCoordinates(pos.x, _map->getMapWidth()),
            pos.y,
            translateFigureCoordinates(pos.y, _map->getMapDepth())
    });
    Explosion->id = id;
    _em->Assign<Sprite>(id, Sprite{Explosion});
    _window->queueDrawable(Explosion);
    return true;
}