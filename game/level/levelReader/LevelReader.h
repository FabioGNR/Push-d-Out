#pragma once

#include "external/JSON/json.hpp"
#include <game/level/LevelDomain.h>
#include <string>

using namespace levelDomain;
using json = nlohmann::json;

class levelReader {
public:
    static json readJSON(std::string fileName);
    static level getLevel(json j);
    static void createEntities(level level);
};