#pragma once

#include "external/JSON/json.hpp"
#include <string>

using json = nlohmann::json;

namespace game {
namespace level {

    struct Theme {
        std::string name;
        std::string sprites;
        std::string trackName;

        double friction = 0.0;
        double gravity = 0.0;

        Theme() = default;
    };

    void to_json(json&, const Theme&);
    void from_json(const json&, Theme&);
}
}
