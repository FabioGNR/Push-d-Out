#pragma once
#include <chrono>
#include <engine/ecs/Component.h>
namespace game::components {
struct PunchComponent : public engine::ecs::BaseComponent<PunchComponent> {
    bool canPunch{ false };
    std::chrono::nanoseconds timeSincePunch{ 0 };
};
}