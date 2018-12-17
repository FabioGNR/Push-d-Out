#pragma once

#include <engine/ecs/System.h>
#include <engine/ecs/World.h>

#include <game/components/LevelMetaComponent.h>

namespace game {
namespace systems {
    class BackgroundSystem : public engine::ecs::BaseSystem<BackgroundSystem> {
    public:
        explicit BackgroundSystem(engine::ecs::World& ecsWorld, common::Vector2D<int> screenSize)
            : m_ecsWorld{ ecsWorld }
            , m_screenSize{ screenSize }
        {
            m_ecsWorld.forEachEntityWith<components::LevelMetaComponent>([&](engine::ecs::Entity& entity) {
                auto levelMeta = m_ecsWorld.getComponent<components::LevelMetaComponent>(entity);
                m_sprite = "assets/sprites/themes/" + levelMeta.theme.sprites + "/background.png";
            });
        }

        void update(std::chrono::nanoseconds timeStep) override;
        void render(engine::IRenderer& renderer) override;

    private:
        std::string m_sprite;
        engine::ecs::World& m_ecsWorld;
        common::Vector2D<int> m_screenSize;
    };
}
}
