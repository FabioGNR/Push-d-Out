#pragma once

#include <string>
#include <game/level/levelDomain.h>
#include "external/JSON/json.hpp"

using namespace levelDomain;
using json = nlohmann::json;

class levelReader {
public:
    static json readJSON(std::string fileName);
    static level getLevel(json j);
    static void createEntities(level level);
};