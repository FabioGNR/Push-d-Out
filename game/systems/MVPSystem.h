#pragma once

#include <engine/ecs/System.h>
#include <engine/ecs/World.h>

namespace game {
namespace systems {
    using EntityId = uint64_t;
    class MVPSystem : public engine::ecs::BaseSystem<MVPSystem> {
    private:
        engine::ecs::World* m_world;
        EntityId m_entityId;

    public:
        explicit MVPSystem(engine::ecs::World* world, EntityId entityId)
            : m_world{ world }
            , m_entityId{ entityId } {};
        void update(std::chrono::nanoseconds timeStep) override;
        void render(engine::IRenderer& renderer) override;
    };
}
}
