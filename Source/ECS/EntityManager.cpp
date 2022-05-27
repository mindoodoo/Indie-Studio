/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** EntityManager
*/

#include "EntityManager.hpp"

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
}

EntityID EntityManager::CreateNewEntity()
{
    if (!freeEntities.empty()) {
        EntityIndex newIndex = freeEntities.back();
        freeEntities.pop_back();
        EntityID newID = CreateEntityId(newIndex, GetEntityVersion(entities[newIndex].id));
        entities[newIndex].id = newID;
        return entities[newIndex].id;
    }
    entities.push_back({ CreateEntityId(EntityIndex(entities.size()), 0), ComponentMask() });
    return entities.back().id;
}

void EntityManager::DestroyEntity(EntityID id)
{
    EntityID newID = CreateEntityId(EntityIndex(-1), GetEntityVersion(id) + 1);
    entities[GetEntityIndex(id)].id = newID;
    entities[GetEntityIndex(id)].mask.reset(); 
    freeEntities.push_back(GetEntityIndex(id));
}

template <typename T>
T *EntityManager::Assign(EntityID id)
{
    // ensures you're not accessing an entity that has been deleted
    if (entities[GetEntityIndex(id)].id != id)
        return;
    int componentId = GetId<T>();

    if (componentPools.size() <= componentId) // Not enough component pool
        componentPools.resize(componentId + 1, nullptr);
    if (componentPools[componentId] == nullptr) // New component, make a new pool
        componentPools[componentId] = new ComponentPool(sizeof(T));

    // Looks up the component in the pool, and initializes it with placement new
    T *pComponent = new (componentPools[componentId]->get(GetEntityIndex(id))) T();

    // Set the bit for this component to true and return the created component
    entities[GetEntityIndex(id)].mask.set(componentId);
    return pComponent;
}

template <typename T>
T *EntityManager::Get(EntityID id)
{
    // ensures you're not accessing an entity that has been deleted
    if (entities[GetEntityIndex(id)].id != id)
        return nullptr;
    int componentId = GetId<T>();
    if (!entities[GetEntityIndex(id)].mask.test(componentId))
        return nullptr;

    T *pComponent = static_cast<T *>(componentPools[componentId]->get(GetEntityIndex(id)));
    return pComponent;
}

template <typename T>
void EntityManager::Remove(EntityID id)
{
    // ensures you're not accessing an entity that has been deleted
    if (entities[GetEntityIndex(id)].id != id)
        return;

    int componentId = GetId<T>();
    entities[GetEntityIndex(id)].mask.reset(componentId);
}
