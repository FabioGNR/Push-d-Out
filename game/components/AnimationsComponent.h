#pragma once
#include <engine/ecs/Component.h>
#include <game/components/SpriteComponent.h>
#include <string>

namespace game::components {
struct AnimationsComponent : public engine::ecs::BaseComponent<AnimationsComponent> {
    std::map<std::string, components::SpriteComponent> animations{};
    AnimationsComponent(std::map<std::string, components::SpriteComponent> animations)
        : animations{ animations }
    {
    }
};
}