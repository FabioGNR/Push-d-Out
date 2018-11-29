#pragma once

#include <chrono>
#include <engine/ecs/System.h>
#include <engine/ecs/World.h>
#include <engine/graphics/Camera.h>
#include <engine/graphics/IRenderer.h>
#include <engine/physics/World.h>
#include <memory>

namespace game {
namespace systems {
    class GarbageCollectorSystem : public engine::ecs::BaseSystem<GarbageCollectorSystem> {
    public:
        explicit GarbageCollectorSystem(engine::ecs::World* ecsWorld, engine::physics::World* physWorld)
            : m_ecsWorld{ ecsWorld }
            , m_physWorld{ physWorld }
        {
        }

        void update(std::chrono::nanoseconds timeStep) override;
        void render(engine::IRenderer& renderer) override;

    private:
        engine::ecs::World* m_ecsWorld;
        engine::physics::World* m_physWorld;

        void cleanUpEntity(engine::ecs::Entity* entityToDestroy);
    };
}
}