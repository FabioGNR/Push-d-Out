#include "BackgroundSystem.h"
#include <game/components/LevelMetaComponent.h>

namespace game {
namespace systems {

    void BackgroundSystem::update(std::chrono::nanoseconds timeStep) {
        m_ecsWorld.forEachEntityWith<components::LevelMetaComponent>([&](engine::ecs::Entity& entity) {
            auto levelMeta = m_ecsWorld.getComponent<components::LevelMetaComponent>(entity);
            m_sprite = "assets/sprites/themes/" + levelMeta.theme.sprites + "/background.png";
        });
    }

    void BackgroundSystem::render(engine::IRenderer &renderer) {
        engine::Sprite sprite{m_sprite, {0,0}, {0,0}, {0,0}};
        sprite.setSize(m_screenSize);
        renderer.draw(sprite);
    }
}
}