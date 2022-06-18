/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** Bomberman
*/

#ifndef BOMBERMAN_HPP_
#define BOMBERMAN_HPP_

#include <vector>
#include "ISystem.hpp"
#include "MovementSystem.hpp"
#include "CollisionSystem.hpp"
#include "DrawSystem.hpp"
#include "AISystem.hpp"
#include "AudioSystem.hpp"
#include "Timer.hpp"
#include "../Raylib/Drawables/Drawable3D.hpp"
#include "../Raylib/InputManager.hpp"
#include "../GameEngine/Map.hpp"
#include "../Raylib/Window.hpp"
#include "SoundManager.hpp"
#include "Timer.hpp"
#include "../Savegame/SaveManager.hpp"

class Bomberman {
    public:
        Bomberman(std::shared_ptr<RL::Window> Window, std::shared_ptr<RL::InputManager> InputManager, std::shared_ptr<RL::Map> Map, std::shared_ptr<RL::SoundManager> SoundManager, std::shared_ptr<RL::SaveManager> SaveManager);
        ~Bomberman();
        std::shared_ptr<EntityManager> getEm();


        void generateItems();
        void generateItemsLoadGame(Pos pos, Skillset skill);
        void createPlayer(Pos pos);
        void createPlayerLoadGame(Pos pos, Skillset skill, int score, BombCapacity capa);
        void createAI(Pos pos);
        void createAILoadGame(Pos pos, Skillset skill, int score, BombCapacity capa);
        void createSpeedUpItem(Pos pos, bool hidden);
        void createBombUpItem(Pos pos, bool hidden);
        void createFireUpItem(Pos pos, bool hidden);
        void createWallPassItem(Pos pos, bool hidden);
        void createMonster(Pos pos);
        void layBomb(EntityID playerid);
        void checkBombalive();
        bool createBomb(Pos pos, EntityID bombOwner, Skillset skillset, float time);
        void checkInput();
        void getFirstPlayerInput();
        void getSecondPlayerInput();
        void startGameTimers();
        void stopGameTimers();
        int runFrame();
        bool checkIfVectorContain(std::vector<EntityID> vector, EntityID id);
        void startDrawScene();
        void stopDrawScene();
        void checkGameEnd();
        void createBombExplosions(EntityID ent);
        bool createExplosion(Pos pos, EntityID bombOwner, float time);
        void checkExplosionalive();
        void smoothBombResize(RL::Drawable3D *BombModel);
        RL::Drawable3D* makeDrawable3DPointer(RL::Drawable3D Model);
        bool isGameEnd();
        void pauseBombCounters();
        void resumeBombCounters();

    protected:
    private:
        std::shared_ptr<RL::Window> _window;
        std::shared_ptr<RL::InputManager> _inputManager;
        std::shared_ptr<RL::SoundManager> _soundManager;
        std::shared_ptr<RL::Map> _map;
        std::shared_ptr<RL::SaveManager> _saveManager;
        std::vector<int> _event;
        std::vector<std::shared_ptr<ISystem>> _systems;
        std::vector<EntityID> _player;
        std::vector<EntityID> _aiBombLaying;
        std::shared_ptr<EntityManager> _em;
        std::vector<RL::Drawable3D> _allModels;
        Timer _gameTimer;
        Timer _deltaTimer;
        bool _gamePaused;
        bool _pauseGame;
};

float translateFigureCoordinates(float pos, int borderSize);

#endif /* !BOMBERMAN_HPP_ */
