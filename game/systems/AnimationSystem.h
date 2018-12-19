#pragma once

#include <engine/ecs/System.h>
#include <engine/ecs/World.h>
#include <engine/graphics/Camera.h>
#include <engine/graphics/IGraphicsElement.h>
#include <engine/graphics/IRenderer.h>
#include <engine/graphics/drawable/RectangleShape.h>
#include <engine/graphics/drawable/Sprite.h>
#include <game/components/SpriteComponent.h>
#include <queue>

#include <utility>

class Compare {
public:
    bool operator()(std::pair<int, engine::Sprite>& lhs, std::pair<int, engine::Sprite>& rhs)
    {
        return lhs.first < rhs.first;
    }
};

namespace game {
namespace systems {
    class AnimationSystem : public engine::ecs::BaseSystem<AnimationSystem> {
    private:
        engine::ecs::World* m_world;
        engine::graphics::Camera* m_camera;
        std::vector<std::pair<int, engine::Sprite>> m_sprites;
        std::function<bool(std::pair<int, engine::Sprite>& lhs, std::pair<int, engine::Sprite>& rhs)> compareFunc =
            [](std::pair<int, engine::Sprite>& lhs, std::pair<int, engine::Sprite>& rhs) { return lhs.first < rhs.first; };
        std::priority_queue<std::pair<int, engine::Sprite>, std::vector<std::pair<int, engine::Sprite>>, Compare> pq;

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
