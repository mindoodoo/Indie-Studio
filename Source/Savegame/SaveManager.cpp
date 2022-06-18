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
        std::cout << "Can't open File" << std::endl;
    file.close();
    return content;
}

RL::SaveManager::SaveManager()
{
    _running = false;
    //_mapPath = _directory + ".saveMAP.csv";
    _filepath = _directory +".saveEntitys";
    std::cout << std::endl<< std::endl<< std::endl<< std::endl<< std::endl<< std::endl;
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
    file = loadFile(filename);

    for (int x = 0; x < file.size(); x++) {
        tmp = seperateLine(file[x], ';');
        for (int y = 0; y < tmp.size(); y++) {
            if (tmp[y] == "PLAYER")
                _playerssave.push_back(file[x]);
            if (tmp[y] == "AI")
                _aissave.push_back(file[x]);
            if (tmp[y] == "BOMB")
                _bombssave.push_back(file[x]);
            if (tmp[y] == "ITEM")
                _itemssave.push_back(file[x]);
            if (tmp[y] == "EXPLOSION")
                _explosionssave.push_back(file[x]);
            std::cout << "TEST " << tmp[y] << std::endl <<std::endl;
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
    std::cout << "You get the following mapPath: " << _mapPath << std::endl;
    return _mapPath;
}

bool RL::SaveManager::getLoading()
{
    if (_mapPath == _directory+".saveMAP.csv")
        return false;
    return true;
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
        case -1:
            _mapPath = _directory + ".saveMAP.csv";
            _running = true;
            checkEntitys(_filepath);
            //clearEntityFile();
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
    result.x = stof(tmp[0]);
    result.y = stof(tmp[1]);
    result.z = stof(tmp[2]);

    return result;
}

Pos RL::SaveManager::getPlayerPos(int index)
{
    std::vector<std::string> tmp = seperateLine(_playerssave[index],';');
    for (int x = 0; x < tmp.size(); x++) {
        if (tmp[x] == "PLAYER") {
            return readPos(tmp[2]);
        }
    }
    std::cerr << "Unable to load Player position" << std::endl;
    return Pos{-1,-1,-99};
}

Pos RL::SaveManager::getAIPos(int index)
{
    std::vector<std::string> tmp = seperateLine(_aissave[index],';');
    std::cout <<"Test Pos:" << std::endl;
    for (int x = 0; x < tmp.size(); x++) {
       if (tmp[x] == "AI") {
           return readPos(tmp[2]);
        }
    }
    std::cerr << "Unable to load AI position" << std::endl;
    return Pos{-1,-1,-99};
}


Pos RL::SaveManager::getBombPos(int index)
{
    std::vector<std::string> tmp = seperateLine(_bombssave[index],';');
    for (int x = 0; x < tmp.size(); x++) {
        if (tmp[x] == "BOMB") {
            return readPos(tmp[2]);
        }
    }
    std::cerr << "Unable to load Bomb position" << std::endl;
    return Pos{-1,-1,-99};
}

Pos RL::SaveManager::getItemPos(int index)
{
    std::vector<std::string> tmp = seperateLine(_itemssave[index],';');
    for (int x = 0; x < tmp.size(); x++)
        if (tmp[x] == "ITEM")
            return readPos(tmp[2]);
    std::cerr << "Unable to load Item position" << std::endl;
    return Pos{-1, -1, -99};
}

float RL::SaveManager::getBombTime(int index)
{
    std::vector<std::string> tmp = seperateLine(_bombssave[index],';');
    for (int x = 0; x < tmp.size(); x++) {
        if (tmp[x] == "BOMB")
            return std::stof(seperateLine(tmp[5], '=')[1]);
    }
    std::cerr << "Unable to load Bomb time" << std::endl;
    return -99;
}

float RL::SaveManager::getExploTime(int index)
{
    std::vector<std::string> tmp = seperateLine(_explosionssave[index],';');
    for (int x = 0; x < tmp.size(); x++) {
        if (tmp[x] == "EXPLOSION")
            return std::stof(seperateLine(tmp[5], '=')[1]);
    }
    std::cerr << "Unable to load Bomb time" << std::endl;
    return -99;
}

Skillset RL::SaveManager::getSkillsetBomb(int index)
{
    std::vector<std::string> tmp = seperateLine(_bombssave[index],';');
    for (int x = 0; x < tmp.size(); x++) {
        if (tmp[x] == "BOMB")
            return readSkillset(tmp[3]);
    }
    std::cerr << "Unable to load skillset" << std::endl;
    return Skillset{99,99,99, false};
}

BombCapacity RL::SaveManager::getBombcapPlayer(int index)
{
    std::vector<std::string> tmp = seperateLine(_playerssave[index],';');
    for (int x = 0; x < tmp.size(); x++) {
        if (tmp[x] == "PLAYER") {
            return readBomb(tmp[4]);
        }
    }
    std::cerr << "Unable to load bombcapacizy" << std::endl;
    return BombCapacity{111,111};
}

BombCapacity RL::SaveManager::getBombcapAI(int index)
{
    std::cout << "TEst CAPA" << std::endl;
    std::vector<std::string> tmp = seperateLine(_aissave[index],';');
    for (int x = 0; x < tmp.size(); x++) {
        if (tmp[x] == "AI") {
            return readBomb(tmp[4]);
        }
    }
    std::cerr << "Unable to load bombcapacizy" << std::endl;
    return BombCapacity{111,111};
}

//from player
Skillset RL::SaveManager::getSkillsetPlayer(int index)
{

    std::vector<std::string> tmp = seperateLine(_playerssave[index],';');
    for (int x = 0; x < tmp.size(); x++) {
        if (tmp[x] == "PLAYER")
            return readSkillset(tmp[3]);
    }
    std::cerr << "Unable to load skillset" << std::endl;
    return Skillset{99,99,99, false};
}

Skillset RL::SaveManager::getSkillsetAI(int index)
{
    std::cout << "Test SKill" << std::endl;
    std::vector<std::string> tmp = seperateLine(_aissave[index],';');
    for (int x = 0; x < tmp.size(); x++) {
        if (tmp[x] == "AI") {
            return readSkillset(tmp[3]);
        }
    }
    std::cerr << "Unable to load skillset" << std::endl;
    return Skillset{99,99,99, false};
}

Skillset RL::SaveManager::getSkillsetItem(int index)
{
    std::vector<std::string> tmp = seperateLine(_itemssave[index],';');
    for (int x = 0; x < tmp.size(); x++) {
        if (tmp[x] == "ITEM") {
            return readSkillset(tmp[3]);
        }
    }
    std::cerr << "Unable to load skillset" << std::endl;
    return Skillset{99,99,99, false};
}

int RL::SaveManager::getScorePlayer(int index)
{
    std::vector<std::string> tmp = seperateLine(_playerssave[index],';');
    for (int x = 0; x < tmp.size(); x++) {
        if (tmp[x] == "PLAYER") {
            tmp = seperateLine(tmp[5], '=');
            return stoi(tmp[1]);
        }
    }
    std::cerr << "Unable to load player score" << std::endl;
    return -1;
}

Pos RL::SaveManager::getExploPos(int index)
{
    std::vector<std::string> tmp = seperateLine(_explosionssave[index],';');
    for (int x = 0; x < tmp.size(); x++)
        if (tmp[x] == "EXPLOSION")
            return readPos(tmp[2]);
    std::cerr << "Unable to load EXPLO position" << std::endl;
    return Pos{-1, -1, -99};

}

int RL::SaveManager::getScoreAI(int index)
{
    std::cout << "Test Score" << std::endl;
    std::vector<std::string> tmp = seperateLine(_aissave[index],';');
    for (int x = 0; x < tmp.size(); x++) {
        if (tmp[x] == "AI") {
            tmp = seperateLine(tmp[5], '=');
            return stoi(tmp[1]);
        }
    }
    std::cerr << "Unable to load AI Score" << std::endl;
    return -1;
}

std::vector <std::string> RL::SaveManager::getPlayers()
{
    return _playerssave;
}

std::vector <std::string> RL::SaveManager::getAIs()
{
    return _aissave;
}

std::vector <std::string> RL::SaveManager::getBombs()
{
    return _bombssave;
}

std::vector <std::string> RL::SaveManager::getExplosions()
{
    return _explosionssave;
}

std::vector <std::string> RL::SaveManager::getItems()
{
    return _itemssave;
}

void RL::SaveManager::savePlayer(EntityID id, Pos position, Skillset skill, BombCapacity bombcapa, Score score)
{
    std::string newplayer= "PLAYER;ID="+ std::to_string(id) +";"+ "POS[" + std::to_string(position.x) + "," + std::to_string(position.y) + "," + std::to_string(position.z) +\
    "];SKILL["+ std::to_string(skill.bombUp) + "," + std::to_string(skill.speedUp) +\
    "," + std::to_string(skill.fireUp) + "," + std::to_string(skill.wallPass) + "];BOMB[" + std::to_string(bombcapa.totalAmount) + "," +\
    std::to_string(bombcapa.curCapacity) +"];SCORE="+ std::to_string(int(score.score));
    _playerssave.push_back(newplayer);
}

void RL::SaveManager::saveAis(EntityID id, Pos position, Skillset skill, BombCapacity bombcapa, Score score)
{
    std::string newai= "AI;ID="+ std::to_string(id) +";"+ "POS[" + std::to_string(position.x) + "," + std::to_string(position.y) + "," + std::to_string(position.z) +\
    "];SKILL["+ std::to_string(skill.bombUp) + "," + std::to_string(skill.speedUp) +\
    "," + std::to_string(skill.fireUp) + "," + std::to_string(skill.wallPass) + "];BOMB[" + std::to_string(bombcapa.totalAmount) + "," +\
    std::to_string(bombcapa.curCapacity) +"];SCORE="+ std::to_string(int(score.score));
    _aissave.push_back(newai);
}

void RL::SaveManager::saveBomb(EntityID id, Pos position, Skillset skill, BombOwner owner, float time)
{
    std::string newbomb= "BOMB;ID="+ std::to_string(id) +";"+ "POS[" + std::to_string(position.x) + "," + std::to_string(position.y) + "," + std::to_string(position.z) +\
    "];SKILL["+ std::to_string(skill.bombUp) + "," + std::to_string(skill.speedUp) +\
    "," + std::to_string(skill.fireUp) + "," + std::to_string(skill.wallPass) + "];OWNER="+ std::to_string(owner.id)+";TIME="+std::to_string(time);
    _bombssave.push_back(newbomb);
}

void RL::SaveManager::saveItem(EntityID id, Pos position, Skillset skill)
{
    std::string newitem= "ITEM;ID="+ std::to_string(id) +";"+ "POS[" + std::to_string(position.x) + "," + std::to_string(position.y) + "," + std::to_string(position.z) +\
    "];SKILL["+ std::to_string(skill.bombUp) + "," + std::to_string(skill.speedUp) +\
    "," + std::to_string(skill.fireUp) + "," + std::to_string(skill.wallPass) + "]";
    _itemssave.push_back(newitem);
}

void RL::SaveManager::saveExplosion(EntityID id, Pos position, BombOwner owner, float time)
{
    std::string newitem= "EXPLOSION;ID="+ std::to_string(id) +";"+ "POS[" + std::to_string(position.x) + "," + std::to_string(position.y) + "," + std::to_string(position.z) +\
    "];OWNER=" + std::to_string(owner.id)+";TIME="+std::to_string(time);
            _explosionssave.push_back(newitem);

}

void RL::SaveManager::saveMap(std::vector<std::vector<gfx_tile_t>> map)
{
    _parsedMap = map;
    _mapPath = _directory + ".saveMAP.csv";
    writeMap();
}


void RL::SaveManager::writeMap()
{
    std::ofstream file(_mapPath);
    std::cout << "write into " << _mapPath << std::endl;
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
    //writeEntitys();
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

void RL::SaveManager::clearEntityFile()
{
    std::ofstream file;
    file.open(_filepath, std::ofstream::out | std::ofstream::trunc);
    file.close();
}

void RL::SaveManager::clearBeforeSafe()
{
    _playerssave.clear();
    _aissave.clear();
    _bombssave.clear();
    _explosionssave.clear();
    _itemssave.clear();
    clearEntityFile();

}