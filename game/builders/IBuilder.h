#pragma once

#include <engine/ecs/World.h>
#include <engine/physics/World.h>

namespace game {
namespace builders {
    class IBuilder {
    public:
        IBuilder() = default;
        virtual ~IBuilder() = default;

        IBuilder(const IBuilder& other) = default;
        IBuilder& operator=(const IBuilder& other) = default;

        IBuilder(IBuilder&& other) = default;
        IBuilder& operator=(IBuilder&& other) = default;

        virtual void build() const = 0;
    };
}
}
