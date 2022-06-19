/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** Bomberman
*/

#ifndef BOMBERMAN_HPP_
#define BOMBERMAN_HPP_

#include <vector>
#include <string>
#include "ISystem.hpp"
#include "MovementSystem.hpp"
#include "CollisionSystem.hpp"
#include "DrawSystem.hpp"
#include "AISystem.hpp"
#include "AudioSystem.hpp"
#include "Timer.hpp"
#include "../GameEngine/CollisionManager.hpp"
#include "../Raylib/Drawables/Drawable3D.hpp"
#include "../Raylib/Drawables/Drawable2D.hpp"
#include "../Raylib/InputManager.hpp"
#include "../GameEngine/Map.hpp"
#include "../Raylib/Window.hpp"
#include "SoundManager.hpp"
#include "Timer.hpp"
#include "RaylibTypeEncaps.hpp"
#include "../Raylib/UIManager.hpp"
#include "../Savegame/SaveManager.hpp"

class Bomberman {
    public:
        Bomberman(std::shared_ptr<RL::Window> Window, std::shared_ptr<RL::InputManager> InputManager, std::shared_ptr<RL::Map> Map, std::shared_ptr<RL::SoundManager> SoundManager, std::shared_ptr<RL::SaveManager> SaveManager, std::vector<PlayerChoice> playerChoices, bool coinMode = false);
        ~Bomberman();
        std::shared_ptr<EntityManager> getEm();

        void createPlayer(Pos pos, int character, UIPos uiPos);
        void createAI(Pos pos, int character, UIPos uiPos);

        void generateItems(int wallPassAmount);
        void generateItemsLoadGame(Pos pos, Skillset skill);
        void createPlayerLoadGame(Pos pos, Skillset skill, int score, BombCapacity capa, int character, UIPos uiPos);
        void createAILoadGame(Pos pos, Skillset skill, int score, BombCapacity capa, int character, UIPos uiPos);
        void createSpeedUpItem(Pos pos, bool hidden);
        void createBombUpItem(Pos pos, bool hidden);
        void createFireUpItem(Pos pos, bool hidden);
        void createWallPassItem(Pos pos, bool hidden);
        void createUIPowerIconsForPlayer(Skillset skill, UIPos uiPos, bool continueToRight);
        void createMonster(Pos pos);
        void createCoin(Pos pos);
        void generateCoins();
        void layBomb(EntityID playerid);
        void checkBombalive();
        bool createBomb(Pos pos, EntityID bombOwner, Skillset skillset, float time);
        void checkInput();
        void getFirstPlayerInput();
        void getSecondPlayerInput();
        void startGameTimers();
        void stopGameTimers();
        std::string getGameTime();
        int runFrame();
        bool checkIfVectorContain(std::vector<EntityID> vector, EntityID id);
        void startDrawScene();
        void stopDrawScene();
        void checkGameEnd();
        void createBombExplosions(EntityID ent);
        bool createExplosion(Pos pos, EntityID bombOwner, float time);
        void checkExplosionalive();
        void smoothBombResize(RL::Drawable3D *BombModel);
        RL::Drawable3D* makeDrawable3DPointer(RL::Drawable3D Model, RL::ModelType type = RL::MODEL);
        bool isGameEnd();
        void pauseBombCounters();
        void resumeBombCounters();
        int getTimeasInt();
        std::vector<std::size_t> getDeadPlayers();
        void addRemainingPlayer();

    protected:
    private:
        std::shared_ptr<RL::Window> _window;
        std::shared_ptr<RL::InputManager> _inputManager;
        std::shared_ptr<RL::SoundManager> _soundManager;
        UIManager _uiManager;
        std::shared_ptr<RL::Map> _map;
        RL::CollisionManager _colManager;
        std::shared_ptr<RL::SaveManager> _saveManager;
        std::vector<int> _event;
        std::vector<std::shared_ptr<ISystem>> _systems;
        std::vector<EntityID> _player;
        std::vector<EntityID> _aiBombLaying;
        std::shared_ptr<EntityManager> _em;
        std::vector<RL::Drawable3D> _allModels;
        std::vector<RL::Drawable2D *> _allIcons;
        RL::Drawable2D _background;
        RL::Drawable2D _layout;
        std::vector<std::size_t> _deadPlayers;

        Timer _gameTimer;
        int _maxGameTime;
        Timer _deltaTimer;
        bool _gamePaused;
        bool _pauseGame;
        bool _coinMode;
        int _maxCoins;
};

float translateFigureCoordinates(float pos, int borderSize);

#endif /* !BOMBERMAN_HPP_ */
