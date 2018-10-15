#pragma once

#include "engine/ecs/System.h"
#include "engine/ecs/World.h"
#include "engine/graphics/IGraphicsElement.h"
#include "graphics/IRenderer.h"
#include <graphics/drawable/RectangleShape.h>

namespace game {
namespace systems {
    class RenderSystem : public engine::ecs::BaseSystem<RenderSystem> {
    private:
        engine::ecs::World& world;
        std::vector<engine::RectangleShape> rectangles;
        int m_unitSize;

    public:
        RenderSystem(engine::ecs::World& world, int unitSize)
            : world(world)
            , m_unitSize{ unitSize }
        {
        }
        
        void render(engine::IRenderer& renderer) override;
        void update(std::chrono::nanoseconds timeStep) override;
    };
}
}
