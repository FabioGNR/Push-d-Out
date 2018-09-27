#include <exception>
#include <fstream>
#include <iostream>

#include "game/level/LevelDomain.h"
#include "LevelReader.h"

json levelReader::readJSON(std::string fileName)
{
    std::ifstream i(fileName);
    json j;
    i >> j;
    return j;
}

level levelReader::getLevel(json j)
{
    level level = j;
    return level;
}

void levelReader::createEntities(level level)
{

}
