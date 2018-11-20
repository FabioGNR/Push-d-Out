#include "SpriteDomain.h"

namespace game {
namespace sprite {

    void to_json(json& j, const Animation& a)
    {
        j = json{
            { "name", a.name },
            { "frameCount", a.frameCount },
            { "frameTime", a.frameTime },
            { "frameSize", { { "x", a.frameSize.x }, { "y", a.frameSize.y } } },
            { "topLeft", { { "x", a.topLeft.x }, { "y", a.topLeft.y } } },
            { "offset", { { "x", a.offset.x }, { "y", a.offset.y } } }
        };
    }

    void from_json(const json& j, Animation& a)
    {
        a.name = j.at("name").get<std::string>();
        a.frameCount = j.at("frameCount").get<int>();
        a.frameTime = j.at("frameTime").get<double>();
        auto frameSize = j.at("frameSize").get<json>();
        a.frameSize = common::Vector2D<int>(frameSize.at("x").get<int>(), frameSize.at("y").get<int>());
        auto topLeft = j.at("topLeft").get<json>();
        a.topLeft = common::Vector2D<int>(topLeft.at("x").get<int>(), topLeft.at("y").get<int>());
        auto offset = j.at("offset").get<json>();
        a.offset = common::Vector2D<int>(offset.at("x").get<int>(), offset.at("y").get<int>());
    }

    void to_json(json& j, const AnimationList& l)
    {
        j = json{
            { "Animations", l.animations }
        };
    }

    void from_json(const json& j, AnimationList& l)
    {
        l.animations = j.at("Animations").get<std::vector<Animation>>();
    }

    void to_json(json& j, const common::Vector2D<int>& v)
    {
        j = json{
            { "x", v.x },
            { "y", v.y }
        };
    }

    void from_json(const json& j, common::Vector2D<int>& v)
    {
        v.x = j.at("x").get<int>();
        v.y = j.at("y").get<int>();
    }
}
}