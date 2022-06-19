/*
** EPITECH PROJECT, 2022
** indie_studio
** File description:
** Map
*/

#include "Map.hpp"

RL::Map::Map(std::string mapCSVPath, std::string wallTexturePath, std::string floorTexturePath, std::string crateTexturePath, bool newGame)
:_wallModel(Drawable3D(wallTexturePath, "", "", RL::WALL)), _floorModel(RL::Drawable3D(floorTexturePath, "","", RL::FLOOR)), _crateModel(RL::Drawable3D(crateTexturePath, "", "", RL::CRATE))
{
    this->_parsedMap = parseMap(mapCSVPath);
    this->mapDepth = _parsedMap.size();
    this->mapWidth = _parsedMap[0].size();
    if (newGame)
        generate_all_crates();
    this->_wallTexturepath = wallTexturePath;
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

void RL::Map::removeCrate(RL::Vector2i pos)
{
    if (_parsedMap[pos.y][pos.x].tile == 2)
        _parsedMap[pos.y][pos.x].tile = 0;
}

void RL::Map::removeItem(RL::Vector2i pos)
{
    if (_parsedMap[pos.y][pos.x].tile != 1 && _parsedMap[pos.y][pos.x].tile != 2)
        _parsedMap[pos.y][pos.x].tile = 0;
}

void RL::Map::addItem(RL::Vector2i pos, int itemValue)
{
    if (_parsedMap[pos.y][pos.x].tile != 1 && _parsedMap[pos.y][pos.x].tile != 2)
        _parsedMap[pos.y][pos.x].tile = itemValue;
}

//drawing the map from MAP Class

void RL::Map::draw_map()
{
    Vector3 WallBoxPos = { 0.0f, 0.5f, 0.0f };
    Vector3 WallBoxSize = this->getwallModel().getBoxSize();
    Vector3 FloorBoxPos = { 0.0f, -0.25f, 0.0f };

    Vector2 size = {20.0f, 20.0f};
    //DrawGrid(16.0f, 1.0f);
    //DrawPlane({0, 0 ,0}, size, BLUE);
    

    for (int i = 0; i < mapDepth; i++) {
        for (int j = 0; j < mapWidth; j++) {
            WallBoxPos.x = translateCoordinatestoWorld(j, mapWidth);
            WallBoxPos.z = translateCoordinatestoWorld(i, mapDepth);
            if (_parsedMap[i][j].tile == 1) { // each if here can represend the drawable u want in the map 
                DrawCubeTexture(_wallModel.getTexture(), WallBoxPos, WallBoxSize.x, WallBoxSize.y, WallBoxSize.z, WHITE);           
            }
            if (_parsedMap[i][j].tile == 2) { // each if here can represend the drawable u want in the map  
                DrawCubeTexture(_crateModel.getTexture(), WallBoxPos, WallBoxSize.x, WallBoxSize.y, WallBoxSize.z, WHITE);  
                //DrawSphere(WallBoxPos, 0.5f, WHITE);
                //we can also draw anything else if its in the drawables of the map. we can actually add anything here and draw it while its in the list              
            }
            FloorBoxPos.x = translateCoordinatestoWorld(j, mapWidth);
            FloorBoxPos.z = translateCoordinatestoWorld(i, mapDepth);
            DrawCubeTexture(_floorModel.getTexture(), FloorBoxPos, WallBoxSize.x, WallBoxSize.y - 0.5f, WallBoxSize.z, WHITE);
        }
    }
}

float RL::Map::translateCoordinatestoWorld(int pos, int borderSize)
{
    float newpos = pos - (borderSize / 2);
    if (borderSize % 2 == 0)
        newpos += 0.5;
    return newpos;
}

//random crate generator

bool RL::Map::skip_start_areas(int i, int j)
{
    //check first row 
    if (i == 1 || i == this->mapDepth - 2) {
        if (j == 1 || j == this->mapWidth - 2 || j == 2 || j == this->mapWidth - 3)
            return true;
    }
    //check first column 
    if (j == 1 || j == this->mapWidth - 2) {
        if (i == 1 || i == this->mapDepth - 2 || i == 2 || i == this->mapDepth - 3)
            return true;
    }
    return false;
}

void RL::Map::generate_all_crates()
{
    int placeCrate;
    for (int i = 0; i < mapDepth; i++) {
        for (int j = 0; j < mapWidth; j++) {
            placeCrate = rand() % 100;
            if (!skip_start_areas(i, j) && _parsedMap[i][j].tile == 0 && placeCrate > 25)
                
                //here we do a randomiser and change the tile to == 2;
                _parsedMap[i][j].tile = 2;
            }
        }
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

RL::Drawable3D RL::Map::getwallModel()
{
    return this->_wallModel;
}
