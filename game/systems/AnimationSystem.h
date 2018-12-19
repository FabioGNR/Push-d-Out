#pragma once

#include <engine/ecs/System.h>
#include <engine/ecs/World.h>
#include <engine/graphics/Camera.h>
#include <engine/graphics/IGraphicsElement.h>
#include <engine/graphics/IRenderer.h>
#include <engine/graphics/drawable/RectangleShape.h>
#include <engine/graphics/drawable/Sprite.h>
#include <game/components/SpriteComponent.h>

#include <utility>

namespace game {
namespace systems {
    class AnimationSystem : public engine::ecs::BaseSystem<AnimationSystem> {
    private:
        engine::ecs::World* m_world;
        engine::graphics::Camera* m_camera;
        std::vector<engine::Sprite> m_sprites;

        void advanceFrame(components::SpriteComponent& spriteComponent);

    public:
        AnimationSystem(engine::ecs::World* world, engine::graphics::Camera* camera)
            : m_world(world)
            , m_camera{ std::move(camera) }
        {
        }

        void render(engine::IRenderer& renderer) override;
        void update(std::chrono::nanoseconds timeStep) override;
    };
}
}
