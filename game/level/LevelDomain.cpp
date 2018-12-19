#include "LevelDomain.h"

#include <engine/exceptions/ResourceNotFoundException.h>
#include <external/JSON/json.hpp>
#include <game/level/reader/ThemeReader.h>

using json = nlohmann::json;

namespace game {
namespace level {
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

    void to_json(json& j, const Prop& p)
    {
        j = json{
            { "x", p.x },
            { "y", p.y },
            { "sprite", p.sprite },
        };
    }

    void from_json(const json& j, Prop& p)
    {
        p.x = j.at("x").get<double>();
        p.y = j.at("y").get<double>();
        p.sprite = j.at("sprite").get<std::string>();
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
            { "Meta", { { "name", l.name }, { "theme", l.theme.name }, { "height", l.height }, { "width", l.width } } },
            { "PlatformTiles", l.tiles },
            { "Props", l.props },
            { "CharacterSpawns", l.CharacterSpawns },
            { "EquipmentSpawns", l.EquipmentSpawns }
        };
    }

    void from_json(const json& j, Level& l)
    {
        json Meta = j.at("Meta").get<json>();
        l.name = Meta.at("name").get<std::string>();
        l.height = Meta.at("height").get<int>();
        l.width = Meta.at("width").get<int>();
        l.tiles = j.at("PlatformTiles").get<std::vector<Tile>>();
        if (j.find("Props") != j.end()) {
            l.props = j.at("Props").get<std::vector<Prop>>();
        }
        l.CharacterSpawns = j.at("CharacterSpawns").get<std::vector<SpawnPoint>>();
        l.EquipmentSpawns = j.at("EquipmentSpawns").get<std::vector<SpawnPoint>>();

        auto themeName = Meta.at("theme").get<std::string>();

        ThemeReader tr{};
        auto json = tr.parse("assets/themes/" + themeName + ".json");
        l.theme = tr.build(json);
    }
}
}