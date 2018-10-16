#include <utility>

#pragma once

#include "graphics/Camera.h"
#include <chrono>
#include <ecs/System.h>
#include <graphics/IRenderer.h>
#include <memory>

namespace game {
namespace systems {
    class CameraSystem : public engine::ecs::BaseSystem<CameraSystem> {
    public:
        CameraSystem(std::shared_ptr<engine::graphics::Camera> camera)
            : m_camera{ std::move(camera) }
        {
        }

        void update(std::chrono::nanoseconds timeStep) override;
        void render(engine::IRenderer& renderer) override;

    private:
        std::shared_ptr<engine::graphics::Camera> m_camera;
    };
}
}