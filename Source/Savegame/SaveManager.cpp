/*
** EPITECH PROJECT, 2022
** .
** File description:
** .
*/
#include "SaveManager.hpp"

std::vector<std::string> seperateLine(std::string line, char sep)
{
    std::vector<std::string> result;
    std::string tmp;
    for (int x = 0; x < line.size(); x++) {
        if (line[x] == sep) {
            result.push_back(tmp);
            tmp.clear();
            tmp.resize(0);
            continue;
        }
        tmp.push_back(line[x]);
    }
    result.push_back(tmp);
    return result;
}

std::vector<std::string> loadFile(std::string path)
{
    std::fstream file;
    std::string tmp;
    std::vector<std::string> content;
    file.open(path);

    if (file.is_open())
        while(std::getline(file, tmp)) {
            content.push_back(tmp);
        }
    else
        std::cout << "Can't open SaveMap" << std::endl;
    file.close();
    return content;
}

RL::SaveManager::SaveManager()
{
    _running = false;
    std::cout << std::endl<< std::endl<< std::endl<< std::endl<< std::endl<< std::endl;
    loadMenu();
    if (_running) {
        checkEntitys(seperateLine(_menu.front(), '=')[2]);
        _mapPath = _directory + ".saveMAP.csv";
    }

    std::cout << std::endl<< std::endl<< std::endl<< std::endl<< std::endl<< std::endl;
}

void RL::SaveManager::loadMenu()
{
    std::vector<std::string> tmp;
    _menu = loadFile("Source/Savegame/SaveFiles/.saveMAIN");
    for (int x = 0; x < _menu.size(); x++) {
        tmp = seperateLine(_menu[x], '=');
        for (int y = 0; y < tmp.size(); y++) {
            checkRunning(tmp, y);
        }
        std::cout << _menu[x] << std::endl;
    }


}

void RL::SaveManager::checkRunning(std::vector<std::string> line, int index)
{
    if (line[index] == "running") {
        if (line[1] == "true") {
            _running = true;
            _filepath = "Source/Savegame/SaveFiles/" + line[2];
        }
    }

}

void RL::SaveManager::checkEntitys(std::string filename)
{
    std::vector<std::string> file;
    std::vector<std::string> tmp;
    std::cout << "Load Entitys in file: " << filename << std::endl;
    file = loadFile(_directory+filename);

    for (int x = 0; x < file.size(); x++) {
        tmp = seperateLine(file[x], ';');
        for (int y = 0; y < tmp.size(); y++) {
            if (tmp[y] == "PLAYER")
                loadEntity(file[x]);
            if (tmp[y] == "AI")
                loadEntity(file[x]);
            if (tmp[y] == "BOMB")
                loadEntity(file[x]);
            if (tmp[y] == "ITEM")
                loadEntity(file[x]);
            std::cout << "TEST " << tmp[y] << std::endl;
        }
    }
}

void RL::SaveManager::loadEntity(std::string line)
{
    _entitys.push_back(line);
}

std::vector <std::string> RL::SaveManager::getMenu()
{
    return _menu;
}



std::string RL::SaveManager::getMappath()
{
    return _mapPath;
}

void RL::SaveManager::updateMap(int map)
{
    switch (map) {
        case 0:
            _mapPath = "RaylibTesting/Assets/Maps/TestMap/test.csv";
            break;
        case 1:
            _mapPath = "RaylibTesting/Assets/Maps/TestMap1/test.csv";
            break;
    }
}

BombCapacity readBomb(std::string line)
{
    BombCapacity result;
    std::vector<std::string> tmp;
    for (int x = 0; x < line.size(); x++) {
        if (line[x] == '[') {
            tmp = seperateLine(line, '[');
            tmp = seperateLine(tmp[1], ']');
            break;
        }
    }
    tmp = seperateLine(tmp[0], ',');
    result.totalAmount= stoi(tmp[0]);
    result.curCapacity = stoi(tmp[1]);
    return result;

}

Pos readPos(std::string line)
{
    Pos result;
    std::vector<std::string> tmp;
    for (int x = 0; x < line.size(); x++) {
        if (line[x] == '[') {
            tmp = seperateLine(line, '[');
            tmp = seperateLine(tmp[1], ']');
            break;
        }
    }
    tmp = seperateLine(tmp[0], ',');
    result.x = stoi(tmp[0]);
    result.y = stoi(tmp[1]);
    result.z = stoi(tmp[2]);

    return result;
}

Pos RL::SaveManager::getPlayerPos(int index)
{
    std::vector<std::string> tmp = seperateLine(_entitys[index],';');
    for (int x = 0; x < tmp.size(); x++) {
        if (tmp[x] == "PLAYER") {
            return readPos(tmp[2]);
        } else if (tmp[x] == "AI") {
            tmp = seperateLine(tmp[5], '=');
            return readPos(tmp[2]);
        }
    }
    std::cerr << "Unable to load Player position" << std::endl;
    return Pos{-1,-1,-99};
}

BombCapacity RL::SaveManager::getBombcap(int index)
{
    std::vector<std::string> tmp = seperateLine(_entitys[index],';');
    for (int x = 0; x < tmp.size(); x++) {
        if (tmp[x] == "PLAYER") {
            return readBomb(tmp[4]);
        } else if (tmp[x] == "AI") {
            tmp = seperateLine(tmp[5], '=');
            return readBomb(tmp[4]);
        }
    }
    std::cerr << "Unable to load bombcapacizy" << std::endl;
    return BombCapacity{111,111};
}

Skillset readSkillset(std::string line)
{
    Skillset result;
    std::vector<std::string> tmp;
    for (int x = 0; x < line.size(); x++) {
        if (line[x] == '[') {
            tmp = seperateLine(line, '[');
            tmp = seperateLine(tmp[1], ']');
            break;
        }
    }
    tmp = seperateLine(tmp[0], ',');
    result.bombUp = stoi(tmp[0]);
    result.speedUp = stoi(tmp[1]);
    result.fireUp = stoi(tmp[2]);
    if (stoi(tmp[3]) == 1)
        result.wallPass = true;
    else
        result.wallPass = false;
    return result;
}

Skillset RL::SaveManager::getSkillset(int index)
{
    std::vector<std::string> tmp = seperateLine(_entitys[index],';');
    for (int x = 0; x < tmp.size(); x++) {
        if (tmp[x] == "PLAYER") {
            return readSkillset(tmp[3]);
        }else if (tmp[x] == "AI") {
            tmp = seperateLine(tmp[5], '=');
            return readSkillset(tmp[3]);
        }
    }
    std::cerr << "Unable to load skillset" << std::endl;
    return Skillset{99,99,99, false};
}

int RL::SaveManager::getScore(int index)
{
    std::vector<std::string> tmp = seperateLine(_entitys[index],';');
    for (int x = 0; x < tmp.size(); x++) {
        if (tmp[x] == "PLAYER") {
            tmp = seperateLine(tmp[5], '=');
            return stoi(tmp[1]);
        } else if (tmp[x] == "AI") {
            tmp = seperateLine(tmp[5], '=');
            return stoi(tmp[1]);
        }
    }
    std::cerr << "Unable to load playerscore" << std::endl;
    return -1;
}

void RL::SaveManager::savePlayer(EntityID id, Pos position, Skillset skill, BombCapacity bombcapa, int score)
{
    std::string newplayer= "PLAYER;ID="+ std::to_string(id) +";"+ "POS[" + std::to_string(position.x) + "," + std::to_string(position.y) + "," + std::to_string(position.z) +\
    "];SKILL["+ std::to_string(skill.bombUp) + "," + std::to_string(skill.speedUp) +\
    "," + std::to_string(skill.fireUp) + "," + std::to_string(skill.wallPass) + "];BOMB[" + std::to_string(bombcapa.totalAmount) + "," +\
    std::to_string(bombcapa.curCapacity) +"];SCORE="+ std::to_string(score);
    _playerssave.push_back(newplayer);
}

void RL::SaveManager::saveAis(EntityID id, Pos position, Skillset skill, BombCapacity bombcapa, int score)
{
    std::string newai= "AI;ID="+ std::to_string(id) +";"+ "POS[" + std::to_string(position.x) + "," + std::to_string(position.y) + "," + std::to_string(position.z) +\
    "];SKILL["+ std::to_string(skill.bombUp) + "," + std::to_string(skill.speedUp) +\
    "," + std::to_string(skill.fireUp) + "," + std::to_string(skill.wallPass) + "];BOMB[" + std::to_string(bombcapa.totalAmount) + "," +\
    std::to_string(bombcapa.curCapacity) +"];SCORE="+ std::to_string(score);
    _aissave.push_back(newai);
}

void RL::SaveManager::saveBomb(EntityID id, Pos position, Skillset skill, BombOwner owner)
{
    std::string newbomb= "BOMB;ID="+ std::to_string(id) +";"+ "POS[" + std::to_string(position.x) + "," + std::to_string(position.y) + "," + std::to_string(position.z) +\
    "];SKILL["+ std::to_string(skill.bombUp) + "," + std::to_string(skill.speedUp) +\
    "," + std::to_string(skill.fireUp) + "," + std::to_string(skill.wallPass) + "];OWNER="+ std::to_string(owner.id);
    _bombssave.push_back(newbomb);
}

void RL::SaveManager::saveItem(EntityID id, Pos position, Skillset skill)
{
    std::string newitem= "ITEM;ID="+ std::to_string(id) +";"+ "POS[" + std::to_string(position.x) + "," + std::to_string(position.y) + "," + std::to_string(position.z) +\
    "];SKILL["+ std::to_string(skill.bombUp) + "," + std::to_string(skill.speedUp) +\
    "," + std::to_string(skill.fireUp) + "," + std::to_string(skill.wallPass) + "]";
    _itemssave.push_back(newitem);
}

void RL::SaveManager::saveMap(std::vector<std::vector<gfx_tile_t>> map)
{
    _parsedMap = map;
    writeMap();
}


void RL::SaveManager::writeMap()
{
    std::ofstream file(_mapPath);
    for (int x = 0; x < _parsedMap.size(); x++) {
        for (int y = 0; y < _parsedMap[x].size(); y++) {
            file << _parsedMap[x][y].tile;
            if (y+1 != _parsedMap[x].size())
                file << ',';
        }
        file  << std::endl;
    }
    file.close();
}

void RL::SaveManager::writeMenu()
{
    _directory = "Source/Savegame/SaveFiles/";
    std::ofstream file(_directory+".saveMAIN");
    file << "running=true=.saveEntitys\n";
    file << "PLAYERS=";

    for (int x=0; x < _playerssave.size(); x++) {
        //add id from player on top of file
        file << seperateLine(seperateLine(_playerssave[x], ';')[1], '=')[1]+ ';';
    }
    //add ai
    file << "\nAI=";
    for (int x = 0; x < _aissave.size(); x++)
        file << seperateLine(seperateLine(_aissave[x], ';')[1], '=')[1]+ ';';
    //add items
    file << "\nITEMS=";
    for (int x = 0; x < _itemssave.size(); x++)
        file << seperateLine(seperateLine(_itemssave[x], ';')[1], '=')[1]+ ';';
    //add Bomb
    file << "\nBOMBS=";
    for (int x = 0; x < _bombssave.size(); x++)
        file << seperateLine(seperateLine(_bombssave[x], ';')[1], '=')[1]+ ';';

    //add explosions
    file << "\nEXPLOSIONS=";
    for (int x = 0; x < _explosionssave.size(); x++)
        file << seperateLine(seperateLine(_explosionssave[x], ';')[1], '=')[1]+ ';';

    file.close();
    writeEntitys();
}

void RL::SaveManager::writeEntitys()
{
    std::ofstream file(_directory +".saveEntitys");

    for (int x = 0; x < _playerssave.size(); x++)
        file << _playerssave[x] << std::endl;

    for (int x = 0; x < _aissave.size(); x++)
        file << _aissave[x] << std::endl;

    for (int x = 0; x < _itemssave.size(); x++)
        file << _itemssave[x] << std::endl;

    for (int x = 0; x < _bombssave.size(); x++)
        file << _bombssave[x] << std::endl;

    for (int x = 0; x < _explosionssave.size(); x++)
        file << _explosionssave[x] << std::endl;
    file.close();
}
