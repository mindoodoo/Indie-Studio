/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** ECS
*/

#ifndef ECS_HPP_
#define ECS_HPP_

#include <bitset>

extern int counter;
const int MAX_COMPONENTS = 32;
const int MAX_ENTITIES = 5000;
typedef unsigned int EntityIndex;
typedef unsigned int EntityVersion;
typedef unsigned long long EntityID;
typedef std::bitset<MAX_COMPONENTS> ComponentMask;

template <class T>
int GetId()
{
    static int curCounter = counter++;
    return curCounter;
}

inline EntityID CreateEntityId(EntityIndex index, EntityVersion version)
{
    // Shift the index up 32, and put the version in the bottom
    return ((EntityID)index << 32) | ((EntityID)version);
}
inline EntityIndex GetEntityIndex(EntityID id)
{
    // Shift down 32 so we lose the version and get our index
    return id >> 32;
}
inline EntityVersion GetEntityVersion(EntityID id)
{
    // Cast to a 32 bit int to get our version number (loosing the top 32 bits)
    return (EntityVersion)id;
}
inline bool IsEntityValid(EntityID id)
{
    // Check if the index is our invalid index
    return (id >> 32) != EntityIndex(-1);
}

#define INVALID_ENTITY CreateEntityId(EntityIndex(-1), 0)

#endif /* !ECS_HPP_ */
