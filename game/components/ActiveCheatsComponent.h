#pragma once
#include <engine/ecs/Component.h>
#include <game/definitions/Cheat.h>
#include <set>

namespace game::components {
struct ActiveCheatsComponent : public engine::ecs::BaseComponent<ActiveCheatsComponent> {
    // this enum can hold multiple active cheats
    std::set<definitions::Cheat> activeCheats{};

    bool isCheatActive(definitions::Cheat cheat) const
    {
        return activeCheats.find(cheat) != activeCheats.end();
    }

    bool hasActiveCheats() const
    {
        return activeCheats.size() > 0;
    }
};
}