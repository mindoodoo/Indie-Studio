/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** ComponentPool
*/

#ifndef COMPONENTPOOL_HPP_
#define COMPONENTPOOL_HPP_

#include <vector>
#include "ECS.hpp"

class ComponentPool
{
    public:
        ComponentPool(size_t elementsize)
        {
            elementSize = elementsize;
            pData = new char[elementSize * MAX_ENTITIES];
        }

        ~ComponentPool()
        {
            delete[] pData;
        }

        void *get(size_t index)
        {
            // looking up the component at the desired index
            return pData + index * elementSize;
        }

    private:
        char *pData{nullptr};
        size_t elementSize{0};
};

#endif /* !COMPONENTPOOL_HPP_ */
