#pragma once

#include <engine/ecs/System.h>
#include <engine/ecs/World.h>

namespace game {
namespace systems {
    class BackgroundSystem : public engine::ecs::BaseSystem<BackgroundSystem> {
    public:
        explicit BackgroundSystem(engine::ecs::World& ecsWorld, common::Vector2D<int> screenSize)
            : m_ecsWorld { ecsWorld }
            , m_screenSize{screenSize}
        {
        }

        void update(std::chrono::nanoseconds timeStep) override;
        void render(engine::IRenderer& renderer) override;

    private:
        std::string m_sprite;
        engine::ecs::World& m_ecsWorld;
        common::Vector2D<int> m_screenSize;
    };
}
}
