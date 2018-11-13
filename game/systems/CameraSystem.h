#pragma once

#include <chrono>
#include <engine/ecs/System.h>
#include <engine/ecs/World.h>
#include <engine/graphics/Camera.h>
#include <engine/graphics/IRenderer.h>
#include <memory>

namespace game {
namespace systems {
    class CameraSystem : public engine::ecs::BaseSystem<CameraSystem> {
    public:
        explicit CameraSystem(engine::ecs::World& ecsWorld, std::shared_ptr<engine::graphics::Camera> camera)
            : m_camera{ std::move(camera) }
            , m_ecsWorld{ ecsWorld }
        {
        }

        void update(std::chrono::nanoseconds timeStep) override;
        void render(engine::IRenderer& renderer) override;

    private:
        std::shared_ptr<engine::graphics::Camera> m_camera;
        engine::ecs::World& m_ecsWorld;
    };
}
}