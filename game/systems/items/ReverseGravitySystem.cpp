#include "ReverseGravitySystem.h"

#include <engine/sound/SDL/SDLSoundManager.h>
#include <game/components/items/ReverseGravityComponent.h>

using namespace game::components::items;

namespace game {
namespace systems {
    namespace items {
        ReverseGravitySystem::ReverseGravitySystem(engine::ecs::World& ecsWorld, engine::physics::World& physicsWorld)
            : m_ecsWorld(ecsWorld)
            , m_physicsWorld(physicsWorld)
        {
            m_soundManager = std::make_unique<engine::sound::SDLSoundManager>();
        }

        void ReverseGravitySystem::update(std::chrono::nanoseconds timeStep)
        {
            std::vector<engine::ecs::Entity*> itemsToBeRemoved{};
            // check if players want to active an item
            m_ecsWorld.forEachEntityWith<ReverseGravityComponent>(
                [&](engine::ecs::Entity& itemEntity) {
                    auto& component = m_ecsWorld.getComponent<ReverseGravityComponent>(itemEntity);
                    if (!component.activated) {
                        reverseGravity();
                        component.activated = true;
                        engine::sound::SoundEffect sound("assets/sounds/reverse-gravity.wav", 0);
                        engine::sound::Volume volume{ 10 };
                        m_soundManager->setSfxVolume(volume);
                        m_soundManager->play(sound);
                    } else {
                        component.timeSinceActivated += timeStep;
                        double secondsSinceFired = std::chrono::duration_cast<std::chrono::milliseconds>(
                                                       component.timeSinceActivated)
                                                       .count()
                            / 1000.0;
                        if (secondsSinceFired > DURATION_SECONDS) {
                            // disable effect and remove item entity
                            reverseGravity();
                            itemsToBeRemoved.push_back(&itemEntity);
                            engine::sound::SoundEffect sound("assets/sounds/reverse-gravity-end.wav", 0);
                            engine::sound::Volume volume{ 10 };
                            m_soundManager->setSfxVolume(volume);
                            m_soundManager->play(sound);
                        }
                    }
                });
            for (auto* item : itemsToBeRemoved) {
                m_ecsWorld.destroyEntity(*item);
            }
        }

        void ReverseGravitySystem::render(engine::IRenderer& /* renderer */) {}

        void ReverseGravitySystem::reverseGravity()
        {
            const auto& currentGravity = m_physicsWorld.getGravity();
            auto newGravity = currentGravity * -1;
            m_physicsWorld.setGravity(newGravity);
        }
    }
}
}