/*
** EPITECH PROJECT, 2022
** indie_studio
** File description:
** CollisionManager
*/

#include "CollisionManager.hpp"

RL::CollisionManager::CollisionManager()
{
}

RL::CollisionManager::~CollisionManager()
{
}

float translateCoordinatestoWorld(int pos, int borderSize)
{
    float newpos = pos - (borderSize / 2);
    if (borderSize % 2 == 0)
        newpos += 0.5;
    return newpos;
}

bool do_collision_walls(Vector3 ModelPos, int i, int j , RL::Map Map)
{
    float x = translateCoordinatestoWorld(j, Map.getMapWidth());
    float z = translateCoordinatestoWorld(i, Map.getMapDepth());


    BoundingBox wallbound;

    wallbound = (BoundingBox){  (Vector3){ x - 0.90f/2,
                                        0.5f - 0.90f/2,
                                        z - 0.90f/2 },
                                (Vector3){ x + 0.90f/2,
                                        0.5f + 0.90f/2,
                                        z + 0.90f/2 }};


    //if (CheckCollisionSpheres(ModelPos, 0.45f, (Vector3){x, 0.5f, z}, 0.48f ))
    if (CheckCollisionBoxSphere(wallbound,ModelPos, 0.40f))
        return true;
    return false;

}

bool RL::CollisionManager::collisionsWithWalls(Vector3 ModelPos, RL::Map Map)
{
    bool collision = false;
    for (int i = 0; i < Map.getMapDepth(); i++) {
        for (int j = 0; j < Map.getMapWidth(); j++) {
            if (Map.getParsedMap()[i][j].tile == 1) {
                //COLLISION HANDLER 
                collision = do_collision_walls(ModelPos, i, j, Map);
                if (collision == true)
                    return collision;
            }   
        }
    }
    return collision;
}

bool RL::CollisionManager::collisionsWithModels(Vector3 MovingPos, RL::Drawable3D Model2)
{
    bool collision = CheckCollisionSpheres(MovingPos, 0.45f, Model2.getPosition(), 0.49f);

    //if model.IS_TRAVERSIBLE == TRUE then
    // collision == false;
    
    return collision;
}