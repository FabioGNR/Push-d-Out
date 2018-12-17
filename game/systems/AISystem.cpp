#include "AISystem.h"
#include <engine/common/RNG.h>
#include <engine/common/Vector2D.h>
#include <engine/graphics/drawable/LineShape.h>
#include <engine/graphics/drawable/RectangleShape.h>
#include <game/components/AIComponent.h>
#include <game/components/MoveComponent.h>
#include <game/components/PositionComponent.h>
#include <game/components/TileComponent.h>

namespace game::systems {
void AISystem::update(std::chrono::nanoseconds timeStep)
{
    m_world->forEachEntityWith<components::AIComponent>([&](auto& entity) {
        auto& ai = m_world->getComponent<components::AIComponent>(entity);
        ai.behaviours[ai.state()]->act(timeStep);
    });
}

void AISystem::render(engine::IRenderer& /* renderer */)
{
}
}
