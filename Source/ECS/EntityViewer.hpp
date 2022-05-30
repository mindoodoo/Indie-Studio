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
class EntityViewer
{
    public:
        EntityViewer(EntityManager& scene) : entityManager(&scene), all(false)
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
                Iterator(EntityManager* entityManager, EntityIndex index, ComponentMask mask, bool all) 
                    : entityManagerI(entityManager), index(index), mask(mask), all(all) {}

                EntityID operator*() const
                {
                    return entityManagerI->getEntities()[index].id;
                }
                
                bool operator==(const Iterator& other) const
                {
                    return index == other.index || index == entityManagerI->getEntities().size();
                }

                bool operator!=(const Iterator& other) const
                {
                    return index != other.index && index != entityManagerI->getEntities().size();
                }

                bool ValidIndex()
                {
                    bool validEntityID = IsEntityValid(entityManagerI->getEntities()[index].id);
                    bool correctComponentMask = (all || mask == (mask & entityManagerI->getEntities()[index].mask));
                    return validEntityID && correctComponentMask;
                }

                Iterator& operator++()
                {
                    do {
                        index++;
                    } while (index < entityManagerI->getEntities().size() && !ValidIndex());
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
            while (firstIndex < entityManager->getEntities().size() &&
                (componentMask != (componentMask & entityManager->getEntities()[firstIndex].mask)
                || !IsEntityValid(entityManager->getEntities()[firstIndex].id)))
            {
                firstIndex++;
            }
            return Iterator(entityManager, firstIndex, componentMask, all);
        }

        const Iterator end() const
        {
            return Iterator(entityManager, EntityIndex(entityManager->getEntities().size()), componentMask, all);
        }

    private:
        EntityManager* entityManager;
        ComponentMask componentMask;
        // will iterate all entities if no ComponentType specified
        bool all;
};


#endif /* !ENTITYVIEWER_HPP_ */
