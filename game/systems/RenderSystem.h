#include <utility>

#pragma once

#include "engine/ecs/System.h"
#include "engine/ecs/World.h"
#include "engine/graphics/IGraphicsElement.h"
#include "graphics/IRenderer.h"
#include <graphics/Camera.h>
#include <graphics/drawable/RectangleShape.h>

namespace game {
namespace systems {
    class RenderSystem : public engine::ecs::BaseSystem<RenderSystem> {
    private:
        engine::ecs::World& world;
        std::shared_ptr<engine::graphics::Camera> m_camera;
        std::vector<engine::RectangleShape> rectangles;

    public:
        RenderSystem(engine::ecs::World& world, std::shared_ptr<engine::graphics::Camera> camera)
            : world(world)
            , m_camera{ std::move(camera) }
        {
        }

        void render(engine::IRenderer& renderer) override;
        void update(std::chrono::nanoseconds timeStep) override;
    };
}
}
