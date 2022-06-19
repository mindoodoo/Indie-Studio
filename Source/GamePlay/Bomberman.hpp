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
#include "../Raylib/Drawables/Drawable2D.hpp"
#include "../Raylib/InputManager.hpp"
#include "../GameEngine/Map.hpp"
#include "../Raylib/Window.hpp"
#include "SoundManager.hpp"
#include "Timer.hpp"
#include "RaylibTypeEncaps.hpp"

class Bomberman {
    public:
        Bomberman(std::shared_ptr<RL::Window> Window, std::shared_ptr<RL::InputManager> InputManager, std::shared_ptr<RL::Map> Map, std::shared_ptr<RL::SoundManager> SoundManager , std::vector<PlayerChoice> playerChoices);
        ~Bomberman();

        void generateItems();
        void createPlayer(Pos pos, int character);
        void createAI(Pos pos, int character);
        void createSpeedUpItem(Pos pos);
        void createBombUpItem(Pos pos);
        void createFireUpItem(Pos pos);
        void createWallPassItem(Pos pos);
        void createMonster(Pos pos);
        void layBomb(EntityID playerid);
        void checkBombalive();
        bool createBomb(Pos pos, EntityID bombOwner, Skillset skillset);
        void checkInput();
        void getFirstPlayerInput();
        void getSecondPlayerInput();
        void startGameTimers();
        void stopGameTimers();
        bool runFrame();
        bool checkIfVectorContain(std::vector<EntityID> vector, EntityID id);
        void startDrawScene();
        void stopDrawScene();
        void checkGameEnd();
        void createBombExplosions(EntityID ent);
        bool createExplosion(Pos pos, EntityID bombOwner);
        void checkExplosionalive();
        void smoothBombResize(RL::Drawable3D *BombModel);
        RL::Drawable3D* makeDrawable3DPointer(RL::Drawable3D Model);
        bool isGameEnd();

    protected:
    private:
        std::shared_ptr<RL::Window> _window;
        std::shared_ptr<RL::InputManager> _inputManager;
        std::shared_ptr<RL::SoundManager> _soundManager;
        std::shared_ptr<RL::Map> _map;
        std::vector<int> _event;
        std::vector<std::shared_ptr<ISystem>> _systems;
        std::vector<EntityID> _player;
        std::vector<EntityID> _aiBombLaying;
        std::shared_ptr<EntityManager> _em;
        std::vector<RL::Drawable3D> _allModels;
        std::vector<RL::Drawable2D *> _allIcons;
        RL::Drawable2D _background;

        Timer _gameTimer;
        Timer _deltaTimer;
        bool _gamePaused;
};

float translateFigureCoordinates(float pos, int borderSize);

#endif /* !BOMBERMAN_HPP_ */
