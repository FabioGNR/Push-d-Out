#pragma once

#include "engine/ecs/Component.h"
#include <iostream>
namespace game {
namespace components {
    struct DirectionComponent : public engine::ecs::BaseComponent<DirectionComponent> {
    private:
        // true is right looking, false is left looking
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