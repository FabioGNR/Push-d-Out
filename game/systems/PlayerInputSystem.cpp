#include "PlayerInputSystem.h"

game::systems::PlayerInputSystem::PlayerInputSystem() = default;

void game::systems::PlayerInputSystem::update(std::chrono::nanoseconds timeStep)
{
    // BaseSystem::update(frameTime);

    // Do something
}

void game::systems::PlayerInputSystem::render(engine::IRenderer& renderer) {}
