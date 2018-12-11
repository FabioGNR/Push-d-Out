#pragma once

#include <engine/ecs/Component.h>
#include <game/ai/Behaviour.h>
#include <game/definitions/AIState.h>
#include <game/definitions/Action.h>

namespace game::components {
struct AIComponent : public engine::ecs::BaseComponent<AIComponent> {
private:
    definitions::AIState m_state = definitions::AIState::WANDERING;

public:
    definitions::AIState state() const
    {
        return m_state;
    }

    void state(definitions::AIState state)
    {
        behaviours[state]->exit();
        m_state = state;
        behaviours[state]->init();
    }

    std::map<definitions::AIState, std::unique_ptr<ai::Behaviour>> behaviours{};
    engine::ecs::Entity* target = nullptr;
};
}
