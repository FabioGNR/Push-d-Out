#include "SpriteSystem.h"

game::systems::SpriteSystem::SpriteSystem() = default;

void game::systems::SpriteSystem::update(std::chrono::nanoseconds /* timeStep */)
{
    // BaseSystem::update(frameTime);

    // Do something
}

void game::systems::SpriteSystem::render(engine::IRenderer& /* renderer */) {}
