#include "PlayerInputSystem.h"

#include <engine/sound/Music.h>
#include <engine/sound/SDL/SDLSoundManager.h>
#include <game/components/MoveComponent.h>
#include <game/components/PlayerInputComponent.h>

using namespace engine::input;

void game::systems::PlayerInputSystem::update(std::chrono::nanoseconds /* timeStep */)
{
    m_world.forEachEntityWith<components::PlayerInputComponent>([&](engine::ecs::Entity& entity) {
        auto& inputMap = m_world.getComponent<components::PlayerInputComponent>(entity).controls;
        auto delta = common::Vector2D<double>(0, 0);

        if (m_keyMap.hasKeyState(inputMap[definitions::Action::MoveLeft], KeyStates::DOWN)) {
            delta.x += -7;
        }
        if (m_keyMap.hasKeyState(inputMap[definitions::Action::MoveRight], KeyStates::DOWN)) {
            delta.x += 7;
        }
        if (m_keyMap.hasKeyState(inputMap[definitions::Action::Jump], KeyStates::PRESSED)) {
            engine::sound::SDLSoundManager soundManager;
            engine::sound::SoundEffect sound("assets/sounds/jump.wav", 0);
            engine::sound::Volume volume{ 10 };
            soundManager.setSfxVolume(volume);
            soundManager.play(sound);

            delta.y += 7;
        }

        if (delta != common::Vector2D<double>(0, 0)) {
            auto move = components::MoveComponent(delta);
            m_world.addComponent<components::MoveComponent>(entity, move);
        }
    });
}

void game::systems::PlayerInputSystem::render(engine::IRenderer& /* renderer */) {}
