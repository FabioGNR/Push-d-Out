//
// Created by Joris on 26-9-2018.
//

#pragma once

#include "external/JSON/json.hpp"
using json = nlohmann::json;

namespace levelDomain {
    struct spawnPoint {
        int x;
        int y;
    };
}
