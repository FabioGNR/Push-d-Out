#pragma once
#include <engine/ecs/Component.h>
#include <game/components/SpriteComponent.h>
#include <string>

namespace game::components {
struct PlayerSpritesComponent : public engine::ecs::BaseComponent<PlayerSpritesComponent> {
    std::map<std::string, components::SpriteComponent> animations{};
    PlayerSpritesComponent(std::map<std::string, components::SpriteComponent> animations)
        : animations{ animations }
    {
    }
};
}