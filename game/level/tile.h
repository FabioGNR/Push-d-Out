#pragma once

#include <string>
#include "external/JSON/json.hpp"
using json = nlohmann::json;
#include "platformKind.h"

namespace levelDomain {
    struct tile {
        int x;
        int y;
        std::string sprite;
        PlatformKind kind;
    };
}

