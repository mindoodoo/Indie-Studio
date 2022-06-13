/*
** EPITECH PROJECT, 2022
** .
** File description:
** .
*/
#include "Bomberman.hpp"

bool Bomberman::createExplosion(Pos pos, EntityID bombOwner)
{
    if (pos.x <= 0 || pos.y <= 0) 
        return false;
    if (pos.x + 1 >= _map->getMapWidth() || pos.y + 1 >= _map->getMapDepth())
        return false;
    std::cout << pos.x << " " << pos.y << std::endl;
    EntityID id = _em->CreateNewEntity();
    _em->Assign<Pos>(id, pos);
    //BOMBOWNER == EXPLOSIONOWNER
    _em->Assign<BombOwner>(id, {bombOwner});
    _em->Assign<CollisionObjectType>(id, CollisionObjectType{EXPLOSION});
    Timer timer = Timer();
    timer.startTimer();
    _em->Assign<Timer>(id, timer);
    float scale = 3;
    // std::string explotex = "./RaylibTesting/Assets/Explosion/textures/fire3lambert1_baseColor.png";
    // std::string explomod = "./RaylibTesting/Assets/Explosion/textures/fire.obj";
    // RL::Drawable3D *Explosion = new RL::Drawable3D(explotex, explomod, "", RL::MODEL, scale);
    RL::Drawable3D *Explosion = makeDrawable3DPointer(_allModels[1]);
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


void Bomberman::checkExplosionalive() {
    for (EntityID ent: EntityViewer<CollisionObjectType, Timer, Sprite>(*_em.get())) {
        if (*_em->Get<CollisionObjectType>(ent) == EXPLOSION) {
            if (_em->Get<Timer>(ent)->returnTime() >= 1) {
                _em->Get<Sprite>(ent)->model->resize(2);
            }
            if (_em->Get<Timer>(ent)->returnTime() >= 1.5) {
                std::cout << "EXPLOSION OVER" << std::endl;
                //delete explosion
                for (int i = 0; i < _window->get3Dqueue().size(); i++) {
                    if (_window->get3Dqueue()[i]->id == ent) {
                        _em->Remove<Sprite>(ent);
                        _window->removeElemtfrom3Dqueue(i);
                        _em->DestroyEntity(ent);

                    }
                }
            }

        }
    }
}