/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** ISystem
*/

#ifndef ISYSTEM_HPP_
#define ISYSTEM_HPP_

#include <memory>
#include "../ECS/EntityViewer.hpp"
#include "Components.hpp"

class ISystem {
    public:
        ~ISystem() = default;

        virtual void update(float deltaTime, std::vector<EntityID> &playerIds, std::vector<EntityID> &aiBombLaying, std::vector<std::size_t> &deadPlayers, int &maxCoins) = 0;
    
    protected:
        std::shared_ptr<EntityManager> _em;
};

#endif /* !ISYSTEM_HPP_ */
