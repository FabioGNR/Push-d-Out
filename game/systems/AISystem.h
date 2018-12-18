#pragma once

#include <engine/ecs/System.h>
#include <engine/ecs/World.h>
#include <engine/graphics/Camera.h>
#include <engine/physics/World.h>

namespace game::systems {
class AISystem : public engine::ecs::BaseSystem<AISystem> {
private:
    engine::ecs::World* m_world;

public:
    explicit AISystem(engine::ecs::World* w)
        : m_world{ w } {};

    void update(std::chrono::nanoseconds timeStep) override;
    void render(engine::IRenderer& renderer) override;
};
}
