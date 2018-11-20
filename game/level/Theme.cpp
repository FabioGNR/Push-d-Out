#include "Theme.h"

namespace game {
namespace level {
    void to_json(json& j, const game::level::Theme& theme)
    {
        j = json{
            { "name", theme.name },
            { "gravity", theme.gravity },
            { "friction", theme.friction },
            { "track", theme.trackName },
            { "sprites", theme.sprites }
        };
    }

    void from_json(const json& j, game::level::Theme& theme)
    {
        theme = Theme();

        theme.name = j["name"];
        theme.trackName = j["track"];
        theme.friction = j.at("friction").get<double>();
        theme.gravity = j.at("gravity").get<double>();
        theme.sprites = j.at("sprites").get<std::string>();
    }
}
}
