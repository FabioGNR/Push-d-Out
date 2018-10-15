#include "JumpSystem.h"

game::systems::JumpSystem::JumpSystem() = default;

void game::systems::JumpSystem::update(std::chrono::nanoseconds /* timeStep */)
{
    // BaseSystem::update(frameTime);

    // Do something
}

void game::systems::JumpSystem::render(engine::IRenderer& /* renderer */) {}
