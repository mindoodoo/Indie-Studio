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
        int _mapselect;
        std::string _filepath;
        std::string _wallPath;
        std::string _floorPath;
        std::string _cratePath;
        std::string _savefilename;
        bool _running;
        bool _coinmode;
        std::vector<std::string> _playerssave;
        std::vector<std::string> _aissave;
        std::vector<std::string> _itemssave;
        std::vector<std::string> _explosionssave;
        std::vector<std::string> _bombssave;
    public:
        SaveManager();
        //Getter
        std::vector<std::string> getMenu();
        bool ifCoinMode();
        std::string getMappath();
        std::string getMapName(int mapid);
        std::string getWallTexture();
        std::string getFloorTexture();
        std::string getCrateTexture();
        bool getLoading();
        int getPlayerChoice(int index);
        Pos getPlayerPos(int index);
        Pos getAIPos(int index);
        Pos getItemPos(int index);
        Pos getBombPos(int index);
        Pos getExploPos(int index);
        BombCapacity getBombcapPlayer(int index);
        BombCapacity getBombcapAI(int index);
        Skillset getSkillsetPlayer(int index);
        Skillset getSkillsetItem(int index);
        Skillset getSkillsetAI(int index);
        Skillset getSkillsetBomb(int index);
        int getScorePlayer(int index);
        int getScoreAI(int index);
        int getTime();
        float getBombTime(int index);
        float getExploTime(int index);
        std::vector<std::string> getPlayers();
        std::vector<std::string> getAIs();
        std::vector<std::string> getItems();
        std::vector<std::string> getBombs();
        std::vector<std::string> getExplosions();

        void loadMenu();
        void checkRunning(std::vector<std::string> line, int index);
        void checkEntitys(std::string filename);
        void loadEntity(std::string line);
        void updateMap(int map);
        void clearEntityFile();
        void clearBeforeSafe();

        void writeMenu();
        void writeMap();
        void writeEntitys();
        //Save --> write in file
        void saveMap(std::vector<std::vector<gfx_tile_t>> map);
        void savePlayer(EntityID id, Pos position, Skillset skill, BombCapacity bombcapa, Score score, int choice);
        void saveBomb(EntityID id, Pos position, Skillset skill, BombOwner owner, float time);
        void saveItem(EntityID id, Pos position, Skillset skill);
        void saveAis(EntityID id, Pos position, Skillset skill, BombCapacity bombcapa, Score score, int choice);
        void saveExplosion(EntityID id, Pos position, BombOwner owner, float time);
        void saveTime(int time);
    };
}

#endif //BOMBERMAN_SAVEMANAGER_HPP