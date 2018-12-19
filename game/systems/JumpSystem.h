#pragma once

#include <engine/ecs/System.h>
#include <engine/ecs/World.h>
#include <engine/physics/ContactListener.h>
#include <engine/physics/World.h>
#include <engine/sound/ISoundManager.h>

namespace game {
namespace systems {
    class JumpSystem : public engine::ecs::BaseSystem<JumpSystem> {
    private:
        engine::ecs::World& m_world;
        engine::sound::ISoundManager* m_soundManager;

        bool mayJump(engine::ecs::Entity&);

    public:
        explicit JumpSystem(engine::ecs::World& world,
            engine::sound::ISoundManager* soundManager)
            : m_world{ world }
            , m_soundManager{ soundManager } {};

        void update(std::chrono::nanoseconds timeStep) override;
        void render(engine::IRenderer& renderer) override;
    };
}
}
