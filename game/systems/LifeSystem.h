#pragma once

#include <engine/ecs/System.h>
#include <engine/ecs/World.h>
#include <engine/graphics/Camera.h>

namespace game {
namespace systems {
    class LifeSystem : public engine::ecs::BaseSystem<LifeSystem> {
    private:
        engine::ecs::World* m_world;
        engine::graphics::Camera* m_camera;

    public:
        LifeSystem(engine::ecs::World* world, engine::graphics::Camera* camera)
            : m_world{ world }
            , m_camera{ camera }
        {
        }

        void update(std::chrono::nanoseconds timeStep) override;
        void render(engine::IRenderer& renderer) override;
    };
}
}
