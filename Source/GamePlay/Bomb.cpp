/*
** EPITECH PROJECT, 2022
** .
** File description:
** .
*/

#include "Bomberman.hpp"
#include <math.h>


bool Bomberman::createBomb(Pos pos, EntityID bombOwner, Skillset skillset)
{
    pos = {round(pos.x),
           round(pos.y),
           round(pos.z)};
    for (EntityID id : EntityViewer<BombOwner, Pos>(*_em.get())) {
        if (pos == *_em->Get<Pos>(id))
            return false;
    }
    EntityID id = _em->CreateNewEntity();
    _em->Assign<Pos>(id, pos);
    _em->Assign<BombOwner>(id, BombOwner{bombOwner});
    _em->Assign<CollisionObjectType>(id, CollisionObjectType{BOMB});
    _em->Assign<Skillset>(id, {skillset});
    Timer timer = Timer();
    timer.startTimer();
    _em->Assign<Timer>(id, timer);
    float scale = 2;
    std::string bombtex = "./RaylibTesting/Assets/3d_models/Skull/Skull.png";
    std::string bombmod = "./RaylibTesting/Assets/3d_models/Skull/Bomb.obj";
    RL::Drawable3D *Bomb = new RL::Drawable3D(bombtex, bombmod, "", RL::MODEL, scale);
    Bomb->setPosition((RL::Vector3f){
            translateFigureCoordinates(pos.x, _map->getMapWidth()),
            pos.y,
            translateFigureCoordinates(pos.y, _map->getMapDepth())
    });
    Bomb->id = id;
    _em->Assign<Sprite>(id, Sprite{Bomb});
    _window->queueDrawable(Bomb);
    return true;
}


void Bomberman::layBomb(EntityID playerid)
{
    std::cout << "LAYING bomb" << std::endl;
    if (_em->Get<BombCapacity>(playerid)->curCapacity >= 1) {
        if (createBomb(*_em->Get<Pos>(playerid), _player[One],*_em->Get<Skillset>(playerid)))
            _em->Get<BombCapacity>(playerid)->curCapacity -= 1;
    }
}

float Bomberman::smoothBombResize(RL::Drawable3D *BombModel)
{
    if (BombModel->getScale() <= 3.01f && BombModel->getUpvalue() == 1) {
        BombModel->resize(BombModel->getScale() + 0.05f);
        if (BombModel->getScale() >= 3.20f)
            BombModel->setUpvalue(0);
        }
    if (BombModel->getScale() >= 0.99f && BombModel->getUpvalue() == 0) {
        BombModel->resize(BombModel->getScale() - 0.015f);
        if (BombModel->getScale() <= 1.00f)
            BombModel->setUpvalue(1);
        }




}

void Bomberman::checkBombalive() {
    for (EntityID ent: EntityViewer<CollisionObjectType, Timer, Sprite, Skillset, BombOwner>(*_em.get())) {
        if (*_em->Get<CollisionObjectType>(ent) == BOMB) {
            //if (_em->Get<Timer>(ent)->returnTime() >= 1) {
            if (_em->Get<Timer>(ent)->returnTime() <= 3) {
                
                //_em->Get<Sprite>(ent)->model->resize(3);
                _em->Get<Sprite>(ent)->model->resize(smoothBombResize(_em->Get<Sprite>(ent)->model));
            }
            if (_em->Get<Timer>(ent)->returnTime() >= 2) {
                std::cout << "BOOOM" << std::endl;
                for (EntityID enty: EntityViewer<BombCapacity>(*_em.get())) {
                    _em->Get<BombCapacity>(enty)->curCapacity += 1;
                }
                //create explosion
                int fireup =  _em->Get<Skillset>(ent)->fireUp;
                Pos mypos = *_em->Get<Pos>(ent);
                    for (int x = 1; x <=  fireup; x++) {
                        createExplosion(mypos , _em->Get<BombOwner>(ent)->id);
                        createExplosion({mypos.x+x,
                                         mypos.y,
                                         1}, _em->Get<BombOwner>(ent)->id);
                        createExplosion({mypos.x-x,
                                         mypos.y,
                                         1}, _em->Get<BombOwner>(ent)->id);
                        createExplosion({mypos.x,
                                         mypos.y+x,
                                         1}, _em->Get<BombOwner>(ent)->id);
                        createExplosion({mypos.x,
                                         mypos.y-x,
                                         1}, _em->Get<BombOwner>(ent)->id);

                }
                //delete bomb
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

