#include "LevelDomain.h"
#include "external/JSON/json.hpp"

using json = nlohmann::json;

namespace game {
namespace levelDomain {

    std::string getSheetName(Theme theme)
    {
        switch (theme) {
        case Theme::Earth:
            return "earthThemeSpriteSheet.png";
        case Theme::Moon:
            return "moonThemeSpriteSheet.png";
        case Theme::Temple:
            return "templeThemeSpriteSheet.png";
        case Theme::City:
            return "cityThemeSpriteSheet.png";
        default:
            throw "Unknown theme";
        }
    }

    // JSON conversions for tile
    void to_json(json& j, const tile& t)
    {
        j = json{
            { "x", t.x },
            { "y", t.y },
            { "sprite", t.sprite },
            { "kind", static_cast<int>(t.kind) }
        };
    }

    void from_json(const json& j, tile& t)
    {
        t.x = j.at("x").get<int>();
        t.y = j.at("y").get<int>();
        t.sprite = j.at("sprite").get<std::string>();
        t.kind = static_cast<PlatformKind>(j.at("kind").get<int>());
    }

    // JSON conversions for spawnPoint
    void to_json(json& j, const spawnPoint& s)
    {
        j = json{
            { "x", s.x },
            { "y", s.y }
        };
    }

    void from_json(const json& j, spawnPoint& s)
    {
        s.x = j.at("x").get<int>();
        s.y = j.at("y").get<int>();
    }

    // JSON conversions for level
    void to_json(json& j, const level& l)
    {
        j = json{
            { "Meta", { { "name", l.name }, { "theme", static_cast<int>(l.theme) }, { "height", l.height }, { "width", l.width } } },
            { "PlatformTiles", l.tiles },
            { "CharacterSpawns", l.CharacterSpawns }
        };
    }

    void from_json(const json& j, level& l)
    {
        json Meta = j.at("Meta").get<json>();
        l.name = Meta.at("name").get<std::string>();
        int themeInt = Meta.at("theme").get<int>();
        if (themeInt > 3) {
            themeInt = 0;
        }
        l.theme = static_cast<Theme>(themeInt);
        l.height = Meta.at("height").get<int>();
        l.width = Meta.at("width").get<int>();
        l.tiles = j.at("PlatformTiles").get<std::vector<tile>>();
        l.CharacterSpawns = j.at("CharacterSpawns").get<std::vector<spawnPoint>>();
    }
}
}