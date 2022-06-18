/*
** EPITECH PROJECT, 2022
** .
** File description:
** .
*/

#ifndef BOMBERMAN_SAVEMANAGER_HPP
#define BOMBERMAN_SAVEMANAGER_HPP

#include "string"
#include "iostream"
#include "vector"
#include "fstream"
#include "../GamePlay/Components.hpp"

namespace RL {
    class SaveManager {
    protected:
        std::vector<std::string> _menu;
        std::vector<std::string> _entitys;
        std::vector<std::vector<gfx_tile_t>> _parsedMap;
        std::string _mapPath;
        std::string _directory = "Source/Savegame/SaveFiles/";
        std::string _filepath;
        std::string _savefilename;
        bool _running;
        std::vector<std::string> _playerssave;
        std::vector<std::string> _aissave;
        std::vector<std::string> _itemssave;
        std::vector<std::string> _explosionssave;
        std::vector<std::string> _bombssave;
    public:
        SaveManager();
        //Getter
        std::vector<std::string> getMenu();
        std::string getMappath();
        bool getLoading();
        Pos getPlayerPos(int index);
        BombCapacity getBombcap(int index);
        Skillset getSkillset(int index);
        int getScore(int index);

        void loadMenu();
        void checkRunning(std::vector<std::string> line, int index);
        void checkEntitys(std::string filename);
        void loadEntity(std::string line);
        void updateMap(int map);

        void writeMenu();
        void writeMap();
        void writeEntitys();
        //Save --> write in file
        void saveMap(std::vector<std::vector<gfx_tile_t>> map);
        void savePlayer(EntityID id, Pos position, Skillset skill, BombCapacity bombcapa, Score score);
        void saveBomb(EntityID id, Pos position, Skillset skill, BombOwner owner);
        void saveItem(EntityID id, Pos position, Skillset skill);
        void saveAis(EntityID id, Pos position, Skillset skill, BombCapacity bombcapa, Score score);
        void saveExplosion(EntityID id, Pos position, BombOwner owner);
    };
}

#endif //BOMBERMAN_SAVEMANAGER_HPP