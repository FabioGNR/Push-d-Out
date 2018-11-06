#pragma once

#include <engine/ecs/System.h>
#include <engine/graphics/Camera.h>
#include <engine/graphics/IRenderer.h>

#include <chrono>
#include <memory>
#include <utility>

namespace game {
namespace systems {
    class CameraSystem : public engine::ecs::BaseSystem<CameraSystem> {
    public:
        explicit CameraSystem(std::shared_ptr<engine::graphics::Camera> camera)
            : m_camera{ std::move(camera) }
        {
            m_camera->setPosition(common::Vector2D<double>(16, 10));
        }

        void update(std::chrono::nanoseconds timeStep) override;
        void render(engine::IRenderer& renderer) override;

    private:
        std::shared_ptr<engine::graphics::Camera> m_camera;
    };
}
}