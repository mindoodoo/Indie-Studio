/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** EntityManager
*/

#ifndef ENTITY_MANAGER_HPP_
#define ENTITY_MANAGER_HPP_

#include <vector>

#include "ECS.hpp"
#include "ComponentPool.hpp"

class EntityManager
{
    public:
        struct EntityDesc
        {
            EntityID id;
            ComponentMask mask;
        };
        EntityManager();
        ~EntityManager();

        EntityID CreateNewEntity();
        void DestroyEntity(EntityID id);

        template<typename T>
        T* Assign(EntityID id);
        template<typename T>
        T* Get(EntityID id);
        template<typename T>
        void Remove(EntityID id);

    private:
        std::vector<EntityDesc> entities;
        std::vector<ComponentPool> componentPools;
        std::vector<EntityIndex> freeEntities;

};
#endif /* !ENTITY_MANAGER_HPP_ */
