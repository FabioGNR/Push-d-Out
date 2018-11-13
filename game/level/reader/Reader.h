#pragma once

#include "external/JSON/json.hpp"
#include "game/level/LevelDomain.h"
#include <engine/ecs/World.h>
#include <engine/exceptions/ResourceNotFoundException.h>
#include <engine/physics/World.h>
#include <fstream>
#include <string>

namespace game {
namespace level {
    using json = nlohmann::json;

    template <typename T>
    class Reader {
    public:
        json parse(const std::string& fileName) const
        {
            std::ifstream i(fileName);
            if (!i.good()) {
                throw ResourceNotFoundException(fileName);
            }
            json j;
            i >> j;
            return j;
        };

        virtual T build(const json& j) = 0;
    };
}
}
