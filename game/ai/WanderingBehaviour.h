#pragma once

#include "Behaviour.h"

namespace game::ai {
class WanderingBehaviour : public Behaviour {
private:
    static constexpr std::chrono::nanoseconds COOLDOWN = std::chrono::seconds(3);
    std::chrono::nanoseconds timeout{ 0 };

    engine::ecs::Entity* findEdge(engine::ecs::Entity*, bool left);
    void setTarget();

public:
    WanderingBehaviour(engine::ecs::World* world, engine::physics::World* physics, engine::ecs::Entity* entity)
        : Behaviour(world, physics, entity){};

    void act(std::chrono::nanoseconds) override;
    void init() override;
    void exit() override;
};
}