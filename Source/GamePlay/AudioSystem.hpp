/*
** EPITECH PROJECT, 2022
** indie_studio
** File description:
** AudioSystem
*/

#ifndef AUDIOSYSTEM_HPP_
#define AUDIOSYSTEM_HPP_

#include "ISystem.hpp"
#include "../GameEngine/Map.hpp"
#include "../Raylib/RaylibTypeEncaps.hpp"
#include "../Window.hpp"
#include "../SoundManager.hpp"

class AudioSystem : public ISystem {
    public:
        AudioSystem(std::shared_ptr<EntityManager> em, std::shared_ptr<RL::SoundManager> soundManager) : _soundManager(soundManager)
        {
            _em = em;
        }
        ~AudioSystem();

        void update(float deltaTime, std::vector<EntityID> &playerIds, std::vector<EntityID> &aiBombLaying, std::vector<std::size_t> &deadPlayers, int &maxCoins) override {
            _soundManager->updateMusicStream();
        }

    protected:
    private:
        std::shared_ptr<RL::SoundManager> _soundManager;
};

#endif /* !AUDIOSYSTEM_HPP_ */
