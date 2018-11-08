#pragma once

#include "external/JSON/json.hpp"
#include <string>
#include <vector>

using json = nlohmann::json;

namespace game {
namespace level {
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

    struct Tile {
        double x{};
        double y{};
        std::string sprite{};
        PlatformKind kind{};
    };

    struct SpawnPoint {
        double x;
        double y;
    };

    struct Level {
        std::string name;
        Theme theme;

        // Size of the Level in Tiles
        int height;
        int width;

        std::vector<Tile> tiles;
        std::vector<SpawnPoint> CharacterSpawns;
        std::vector<SpawnPoint> EquipmentSpawns;
    };

    std::string getSheetName(Theme theme);

    void to_json(json& j, const Tile& t);
    void from_json(const json& j, Tile& t);

    void to_json(json& j, const SpawnPoint& s);
    void from_json(const json& j, SpawnPoint& s);

    void to_json(json& j, const Level& l);
    void from_json(const json& j, Level& l);
}
}
