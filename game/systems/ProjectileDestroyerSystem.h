#pragma once

#include <chrono>
#include <engine/ecs/System.h>
#include <engine/ecs/World.h>
#include <engine/graphics/Camera.h>
#include <engine/graphics/IRenderer.h>
#include <memory>

namespace game {
namespace systems {
    class ProjectileDestroyerSystem : public engine::ecs::BaseSystem<ProjectileDestroyerSystem> {
    public:
        explicit ProjectileDestroyerSystem(engine::ecs::World* ecsWorld, engine::graphics::Camera* camera)
            : m_ecsWorld{ ecsWorld }
            , m_camera{ camera }
        {
        }

        void update(std::chrono::nanoseconds timeStep) override;
        void render(engine::IRenderer& renderer) override;

    private:
        engine::ecs::World* m_ecsWorld;
        engine::graphics::Camera* m_camera;

        common::Vector2D<double> getLevelDimensions() const;
        void markEntityDestructible(engine::ecs::Entity& entity);
    };
}
}