#pragma once

#include <game/definitions/ItemType.h>

#include <engine/ecs/Component.h>
#include <engine/ecs/Entity.h>
#include <engine/physics/Body.h>

#include <chrono>

namespace game {
namespace components {
    namespace items {
        struct ReverseGravityComponent : public engine::ecs::BaseComponent<ReverseGravityComponent> {
            engine::ecs::Entity& itemEntity;
            bool activated = false;
            std::chrono::nanoseconds timeSinceActivated{ 0 };

            explicit ReverseGravityComponent(engine::ecs::Entity& entity)
                : itemEntity{ entity }
            {
            }
        };
    }
}
}