#pragma once

#include "Behaviour.h"

namespace game::ai {
class IdleBehaviour : public Behaviour {
private:
    static constexpr std::chrono::nanoseconds COOLDOWN = std::chrono::seconds(3);
    std::chrono::nanoseconds m_timeout{ 0 };

public:
    IdleBehaviour(engine::ecs::World* world, engine::physics::World* physics, engine::ecs::Entity* entity)
        : Behaviour(world, physics, entity){};

    void act(std::chrono::nanoseconds) override;
    void init() override;
    void exit() override;
};
}