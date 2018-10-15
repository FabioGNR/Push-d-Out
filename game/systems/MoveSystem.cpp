#include "MoveSystem.h"

game::systems::MoveSystem::MoveSystem() = default;

void game::systems::MoveSystem::update(std::chrono::nanoseconds /* timeStep */)
{
    // BaseSystem::update(frameTime);

    // Do something
}

void game::systems::MoveSystem::render(engine::IRenderer& /* renderer */) {}
