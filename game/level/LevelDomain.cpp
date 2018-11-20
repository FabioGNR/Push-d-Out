#include "LevelDomain.h"

#include <engine/exceptions/ResourceNotFoundException.h>
#include <external/JSON/json.hpp>

using json = nlohmann::json;

namespace game {
namespace level {

    std::string getSheetName(Theme theme)
    {
        switch (theme) {
        case Theme::Earth:
            return "Earth";
        case Theme::Moon:
            return "Moon";
        case Theme::Temple:
            return "Temple";
        case Theme::City:
            return "City";
        default:
            throw ResourceNotFoundException("stylesheet");
        }
    }

    std::string getJSONFile(Theme theme)
    {
       return "datafile.json";
    }

    // JSON conversions for tile
    void to_json(json& j, const Tile& t)
    {
        j = json{
            { "x", t.x },
            { "y", t.y },
            { "sprite", t.sprite },
            { "kind", static_cast<int>(t.kind) }
        };
    }

    void from_json(const json& j, Tile& t)
    {
        t.x = j.at("x").get<double>();
        t.y = j.at("y").get<double>();
        t.sprite = j.at("sprite").get<std::string>();
        t.kind = static_cast<PlatformKind>(j.at("kind").get<int>());
    }

    // JSON conversions for spawnPoint
    void to_json(json& j, const SpawnPoint& s)
    {
        j = json{
            { "x", s.x },
            { "y", s.y }
        };
    }

    void from_json(const json& j, SpawnPoint& s)
    {
        s.x = j.at("x").get<double>();
        s.y = j.at("y").get<double>();
    }

    // JSON conversions for Level
    void to_json(json& j, const Level& l)
    {
        j = json{
            { "Meta", { { "name", l.name }, { "theme", static_cast<int>(l.theme) }, { "height", l.height }, { "width", l.width } } },
            { "PlatformTiles", l.tiles },
            { "CharacterSpawns", l.CharacterSpawns },
            { "EquipmentSpawns", l.EquipmentSpawns }
        };
    }

    void from_json(const json& j, Level& l)
    {
        json Meta = j.at("Meta").get<json>();
        l.name = Meta.at("name").get<std::string>();
        auto themeInt = Meta.at("theme").get<int>();
        if (themeInt > 3) {
            themeInt = 0;
        }
        l.theme = static_cast<Theme>(themeInt);
        l.height = Meta.at("height").get<int>();
        l.width = Meta.at("width").get<int>();
        l.tiles = j.at("PlatformTiles").get<std::vector<Tile>>();
        l.CharacterSpawns = j.at("CharacterSpawns").get<std::vector<SpawnPoint>>();
        l.EquipmentSpawns = j.at("EquipmentSpawns").get<std::vector<SpawnPoint>>();
    }
}
}