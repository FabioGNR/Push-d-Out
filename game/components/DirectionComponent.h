#pragma once

#include "engine/ecs/Component.h"

namespace game {
namespace components {
    struct DirectionComponent : public engine::ecs::BaseComponent<DirectionComponent> {
    private:
        // true is left looking, false is right looking
        bool directionLeft = false;

    public:
        bool getDir() const
        {
            return directionLeft;
        }

        void setDir(bool bol)
        {
            directionLeft = bol;
        }
    };
}
}