#include <fstream>
#include <iostream>
#include <exception>


#include "levelReader.h"

json levelReader::readJSON(std::string fileName) {
    try {
        std::ifstream i(fileName);
        json j;
        i >> j;
        return j;
    } catch (std::exception& e) {
        std::cout << e.what() << "\n" << std::endl;
    }
}

level levelReader::getLevel(json j) {
    try {
        level level = j;
        return level;
    } catch(std::exception& e) {
        std::cout << e.what() << "\n" << std::endl;
        return level();
    }
}

void levelReader::createEntities(level level) {

}
