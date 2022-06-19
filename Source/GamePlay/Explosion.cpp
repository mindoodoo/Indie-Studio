/*
** EPITECH PROJECT, 2022
** .
** File description:
** .
*/
#include "Bomberman.hpp"

bool Bomberman::createExplosion(Pos pos, EntityID bombOwner, float time)
{
    if (pos.x <= 0 || pos.y <= 0) 
        return false;
    if (pos.x + 1 >= _map->getMapWidth() || pos.y + 1 >= _map->getMapDepth())
        return false;
    if (_map->getParsedMap()[pos.y][pos.x].tile == 1)
        return false;
    EntityID id = _em->CreateNewEntity();
    _em->Assign<Pos>(id, pos);
    //BOMBOWNER == EXPLOSIONOWNER
    _em->Assign<BombOwner>(id, {bombOwner});
    _em->Assign<CollisionObjectType>(id, CollisionObjectType{EXPLOSION});
    if (time != 0) {
        Timer timer = Timer();
        timer.startTimer();
        timer.setBombtime(time);
        _em->Assign<Timer>(id, timer);
    } else {
        Timer timer = Timer();
        timer.startTimer();
        _em->Assign<Timer>(id, timer);
    }
    float scale = 3;
    // std::string explotex = "./RaylibTesting/Assets/Explosion/textures/fire3lambert1_baseColor.png";
    // std::string explomod = "./RaylibTesting/Assets/Explosion/textures/fire.obj";
    // RL::Drawable3D *Explosion = new RL::Drawable3D(explotex, explomod, "", RL::MODEL, scale);
    RL::Drawable3D *Explosion = makeDrawable3DPointer(_allModels[1]);
    Explosion->setLoadedAnimationTrue();
    Explosion->resize(0.5f);
    //Explosion->loadAnimation("./RaylibTesting/Assets/Explosion/textures/fire.iqm"); // NO GOOD

    Explosion->setCurrentAnim(0);
    Explosion->setPosition((RL::Vector3f){
            translateFigureCoordinates(pos.x, _map->getMapWidth()),
            0.5f,
            translateFigureCoordinates(pos.y, _map->getMapDepth())
    });
    Explosion->id = id;
    _em->Assign<Sprite>(id, Sprite{Explosion});
    _window->queueDrawable(Explosion);
    bool stop = false;
    if (_map->getParsedMap()[pos.y][pos.x].tile == 2)
        stop = true;
    _map->removeCrate({(int)pos.x, (int)pos.y});
    if (_coinMode) {
        for (EntityID ent: EntityViewer<CollisionObjectType, Score, Pos, Sprite>(*_em.get())) {
            CollisionObjectType *objectType = _em->Get<CollisionObjectType>(ent);
            Pos *itemPos = _em->Get<Pos>(ent);
            Sprite *itemAsset = _em->Get<Sprite>(ent);
            if (*objectType == ITEM && itemPos->x == pos.x && itemPos->y == pos.y) {
                itemAsset->model->setHidden(false);
            }
        }
    } else {
        for (EntityID ent: EntityViewer<CollisionObjectType, ItemType, Pos, Sprite>(*_em.get())) {
            CollisionObjectType *objectType = _em->Get<CollisionObjectType>(ent);
            ItemType *itemType = _em->Get<ItemType>(ent);
            Pos *itemPos = _em->Get<Pos>(ent);
            Sprite *itemAsset = _em->Get<Sprite>(ent);
            if (*objectType == ITEM && itemPos->x == pos.x && itemPos->y == pos.y) {
                itemAsset->model->setHidden(false);
                _map->addItem({(int)itemPos->x, (int)itemPos->y}, *itemType);
            }
        }
    }
    if (stop)
        return false;
    //_soundManager->playSpecificSoundFx("Wallsbreak");
    return true;
}


void Bomberman::checkExplosionalive() {
    for (EntityID ent: EntityViewer<CollisionObjectType, Timer, Sprite>(*_em.get())) {
        if (*_em->Get<CollisionObjectType>(ent) == EXPLOSION) {
            if (_em->Get<Timer>(ent)->returnTime() >= 1) {
                _em->Get<Sprite>(ent)->model->resize(0.5f);
            }
            if (_em->Get<Timer>(ent)->returnTime() >= 1.5) {
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