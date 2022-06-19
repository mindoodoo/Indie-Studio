/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include <memory>
#include <vector>

#include "Raylib/Window.hpp"
#include "Raylib/InputManager.hpp"
#include "GameEngine/Map.hpp"
#include "GamePlay/Bomberman.hpp"
#include "GamePlay/ISystem.hpp"
#include "../menu_source/StartMenu.hpp"
#include "../menu_source/EndMenu.hpp"
#include "../menu_source/PauseMenu.hpp"
#include "../menu_source/Settings.hpp"
#include "../menu_source/CharacterSelect.hpp"
#include "../menu_source/MapSelect.hpp"
#include "../Source/Savegame/SaveManager.hpp"

// // Macros for screen switch
#define START_SCREEN 0
#define CHAR_SCREEN 1
#define CHAR_SELEC_TWO 2
#define SETTINGS_SCREEN 3
#define CLOSE 4
#define MAP_SCREEN 5
#define GAME_SCREEN 6
#define PAUSE_SCREEN 7
#define END_SCREEN 8
#define INTRO 9
#define LOAD 10

class Core {
    public:
        Core();
        ~Core();

        void startLoop();
        void killGame();
        void saveGame();

        void startGame();
    private:
        std::shared_ptr<RL::Window> _window;
        std::shared_ptr<RL::InputManager> _inputManager;
        std::shared_ptr<RL::SaveManager> _saveManager;
        std::shared_ptr<RL::Map> _map;
        std::shared_ptr<RL::SoundManager> _soundManager;
        Win::StartMenu *_startMenu = nullptr;
        Win::EndMenu *_endMenu = nullptr;
        Win::PauseMenu *_pauseMenu = nullptr;
        Win::Settings *_settings = nullptr;
        Win::CharacterSelect *_charSelec = nullptr;
        Win::MapSelect *_mapSelect = nullptr;
        Bomberman *_game = nullptr;
        int _prevS;
        int _prevM;
        int _screen;
        std::vector<std::size_t> _allDeadPlayers;
};

#endif /* !CORE_HPP_ */
