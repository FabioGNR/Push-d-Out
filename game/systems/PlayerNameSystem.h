#pragma once

#include <engine/ecs/System.h>
#include <engine/ecs/World.h>
#include <engine/graphics/Camera.h>
#include <game/components/PlayerInputComponent.h>

namespace game {
namespace systems {
    class PlayerNameSystem : public engine::ecs::BaseSystem<PlayerNameSystem> {
    private:
        engine::ecs::World* m_world;
        engine::graphics::Camera* m_camera;

    public:
        PlayerNameSystem(engine::ecs::World* world, engine::graphics::Camera* camera)
            : m_world{ world }
            , m_camera{ camera } {};
        void update(std::chrono::nanoseconds timeStep) override;
        void render(engine::IRenderer& renderer) override;
    };
}
}
