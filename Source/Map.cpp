/*
** EPITECH PROJECT, 2022
** indie_studio
** File description:
** Map
*/

#include "Map.hpp"

RL::Map::Map(std::string mapCSVPath, std::string wallTexturePath)
{
    this->_parsedMap = parseMap(mapCSVPath);
    this->mapDepth = _parsedMap.size();
    this->mapWidth = _parsedMap[0].size();
    this->_wallTexturepath = wallTexturePath;
    //this->_wallTexture = LoadTexture
}

RL::Map::~Map()
{
    this->_parsedMap.clear();
    //this->_mapStaticAssets.clear();
}

std::vector<std::string> csv_read_row(const std::string &line)
{
    std::vector<std::string> row;

    char *c_line = const_cast<char *>(line.c_str());
    char *token = std::strtok(c_line, ",");

    row.emplace_back(token);

    while ((token = std::strtok(nullptr, ","))) {
        row.emplace_back(token);
    }
    return row;
}

std::vector<std::vector<std::string>> csvToTable(const std::string &filepath)
{
    std::vector<std::string> row;
    std::vector<std::vector<std::string>> table;
    std::ifstream myFile(filepath);
    std::string buff;

    if (!myFile.is_open())
        throw std::runtime_error(filepath + ": Could not open file.");
    while (getline(myFile, buff)) {
        row = csv_read_row(buff);
        table.push_back(row);
    }
    myFile.close();
    return table;
}

std::vector<std::string> csvToVector(const std::string &filepath)
{
    std::vector<std::string> row;
    std::vector<std::string> output;
    std::ifstream myFile(filepath);
    std::string buff;

    if (!myFile.is_open())
        throw std::runtime_error(filepath + ": Could not open file.");
    while (getline(myFile, buff)) {
        row = csv_read_row(buff);
        output.insert(output.end(), row.begin(), row.end());
    }
    myFile.close();
    return output;
}

std::vector<std::string> splitStr(std::string str, std::string sep)
{
    std::vector<std::string> output;
    size_t start = 0;
    size_t end;
    std::string token;

    while ((end = str.find(sep, start)) != std::string::npos) {
        token = str.substr(start, end - start);
        start = end + sep.length();
        output.push_back (token);
    }
    output.push_back(str.substr (start));

    return output;
}


std::vector<std::vector<gfx_tile_t>> RL::Map::parseMap(const std::string &path)
{
    std::vector<std::vector<std::string>> parsedCsv = csvToTable(path);
    std::vector<gfx_tile_t> tempRow;
    std::vector<std::string> splitCell;

    std::vector<std::vector<gfx_tile_t> > map;

    for (long unsigned int i = 0; i < parsedCsv.size(); i++) {
        tempRow.clear();

        for (long unsigned int j = 0; j < parsedCsv[i].size(); j++) {
            // Split tile from orientation
            splitCell = splitStr(parsedCsv[i][j], ";");

            // Push new gfx tile to row
            tempRow.push_back({
                stoi(splitCell[0]),
                (splitCell.size() > 1 ? stoi(splitCell[1]) : 0)
            });
        }

        map.push_back(tempRow);
    }
    return map;
}

//Getters

int RL::Map::getMapWidth()
{
    return this->mapWidth;
}

int RL::Map::getMapDepth()
{
    return this->mapDepth;    
}

std::vector<std::vector<gfx_tile_t>> RL::Map::getParsedMap()
{
    return this->_parsedMap;
}


