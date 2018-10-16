#pragma once

#include <engine/ecs/World.h>
#include <engine/physics/World.h>

namespace game {
namespace builders {
    class IBuilder {
    public:
        virtual ~IBuilder() = default;
        virtual void build() const = 0;
    };
}
}
