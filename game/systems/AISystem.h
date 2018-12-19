#pragma once

#include <engine/ecs/System.h>
#include <engine/ecs/World.h>
#include <engine/graphics/Camera.h>
#include <engine/physics/World.h>

namespace game::systems {
class AISystem : public engine::ecs::BaseSystem<AISystem> {
private:
    engine::ecs::World* m_world;
    engine::physics::World* m_physics;
    engine::graphics::Camera* m_camera;

public:
    explicit AISystem(engine::ecs::World* w, engine::physics::World* p, engine::graphics::Camera* c)
        : m_world{ w }
        , m_physics{ p }
        , m_camera{ c } {};

    void update(std::chrono::nanoseconds timeStep) override;
    void render(engine::IRenderer& renderer) override;
};
}
