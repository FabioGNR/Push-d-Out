#include <fstream>
#include <iostream>
#include <exception>


#include "levelReader.h"
#include "../levelDomain.h"

json levelReader::readJSON(std::string fileName) {
    std::ifstream i("D:\\Users\\Joris\\Documents\\HBO-ICT\\Jaar 4\\Minor\\Project\\Push_d_out\\tests\\testjson.JSON");
    json j;
    i >> j;
    return j;
}

level levelReader::getLevel(json j) {
    level level = j;
    return level;
}

void levelReader::createEntities(level level) {
    level.name;
}
