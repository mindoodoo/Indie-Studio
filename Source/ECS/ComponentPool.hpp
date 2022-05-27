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
            data = new char[elementSize * MAX_ENTITIES];
        }

        ~ComponentPool()
        {
            delete[] data;
        }

        void *get(size_t index)
        {
            return data + index * elementSize;
        }

    private:
        char *data;
        size_t elementSize;
};

#endif /* !COMPONENTPOOL_HPP_ */
