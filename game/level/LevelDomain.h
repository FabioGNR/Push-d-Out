#pragma once

#include "external/JSON/json.hpp"
#include <string>
#include <vector>

using json = nlohmann::json;

namespace game {
namespace levelDomain {
    enum class Theme {
        Earth = 0,
        Moon = 1,
        Temple = 2,
        City = 3

    };

    enum class PlatformKind {
        Solid = 0,
        UnderPassable = 1
    };

    struct tile {
        double x;
        double y;
        std::string sprite;
        PlatformKind kind;
    };

    struct spawnPoint {
        double x;
        double y;
    };

    struct level {
        std::string name;
        Theme theme;

        // Size of the level in Tiles
        int height;
        int width;

        std::vector<tile> tiles;
        std::vector<spawnPoint> CharacterSpawns;
        std::vector<spawnPoint> EquipmentSpawns;
    };

    std::string getSheetName(Theme theme);

    void to_json(json& j, const tile& t);

    void from_json(const json& j, tile& t);

    void to_json(json& j, const spawnPoint& t);

    void from_json(const json& j, spawnPoint& t);

    void to_json(json& j, const level& t);

    void from_json(const json& j, level& t);
}
}
