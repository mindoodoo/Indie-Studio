/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** EntityViewer
*/

#ifndef ENTITYVIEWER_HPP_
#define ENTITYVIEWER_HPP_

#include "EntityManager.hpp"

template<typename... ComponentTypes>
class SceneView
{
    public:
        SceneView(EntityManager& scene) : entityManager(&scene) 
        {
            if (sizeof...(ComponentTypes) == 0)
                all = true;
            else {
                // Unpack the template parameters into an initializer list
                int componentIds[] = { 0, GetId<ComponentTypes>() ... };
                for (int i = 1; i < (sizeof...(ComponentTypes) + 1); i++)
                    componentMask.set(componentIds[i]);
            }
        }

        class Iterator
        {
            public:
                Iterator(Scene* entityManager, EntityIndex index, ComponentMask mask, bool all) 
                    : entityManagerI(entityManager), index(index), mask(mask), all(all) {}

                EntityID operator*() const
                {
                    return entityManagerI->entities[index].id;
                }
                
                bool operator==(const Iterator& other) const
                {
                    return index == other.index || index == entityManagerI->entities.size();
                }

                bool operator!=(const Iterator& other) const
                {
                    return index != other.index && index != entityManagerI->entities.size();
                }

                bool ValidIndex()
                {
                    bool validEntityID = IsEntityValid(entityManagerI->entities[index].id);
                    bool correctComponentMask = (all || mask == (mask & entityManagerI->entities[index].mask))
                    return validEntityID && correctComponentMask;
                }

                Iterator& operator++()
                {
                    while (index < entityManagerI->entities.size() && !ValidIndex())
                        index++;
                    return *this;
                }
            
            private:
                EntityIndex index;
                EntityManager* entityManagerI;
                ComponentMask mask;
                bool all{ false };
        };

        const Iterator begin() const
        {
            int firstIndex = 0;
            while (firstIndex < entityManager->entities.size() &&
                (componentMask != (componentMask & entityManager->entities[firstIndex].mask) 
                || !IsEntityValid(entityManager->entities[firstIndex].id))) 
            {
                firstIndex++;
            }
            return Iterator(entityManager, firstIndex, componentMask, all);
        }

        const Iterator end() const
        {
            return Iterator(pScene, EntityIndex(pScene->entities.size()), componentMask, all);
        }

    private:
        EntityManager* entityManager{ nullptr };
        ComponentMask componentMask;
        // will iterate all entities if no ComponentType specified
        bool all{ false };
};


#endif /* !ENTITYVIEWER_HPP_ */
