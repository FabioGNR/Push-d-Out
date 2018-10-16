#include "WeaponSystem.h"
#include <chrono>
#include <graphics/IRenderer.h>
#include "game/components/PlayerInputComponent.h"

namespace game {
namespace systems {
    using namespace components;
    void game::systems::WeaponSystem::update(std::chrono::nanoseconds /* timeStep */)
    {
//        m_ecsWorld.forEachEntityWith<PlayerInputComponent>([&](engine::ecs::Entity& entity) {
//            WeaponType
//        });
    }

    void game::systems::WeaponSystem::render(engine::IRenderer& /* renderer */) {}
}
}
