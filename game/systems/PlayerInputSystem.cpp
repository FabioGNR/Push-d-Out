#include "PlayerInputSystem.h"

#include <engine/sound/Music.h>
#include <engine/sound/SDL/SDLSoundManager.h>
#include <game/components/MoveComponent.h>
#include <game/components/PlayerInputComponent.h>

using namespace engine::input;

void game::systems::PlayerInputSystem::update(std::chrono::nanoseconds /* timeStep */)
{
    m_world.forEachEntityWith<components::PlayerInputComponent>([&](engine::ecs::Entity& entity) {
        auto& PIC = m_world.getComponent<components::PlayerInputComponent>(entity);
        //auto& controlMap = m_world.getComponent<components::PlayerInputComponent>(entity).controls;
        //auto& analogControlMap = m_world.getComponent<components::PlayerInputComponent>(entity).analogControls;
        auto delta = common::Vector2D<double>(0, 0);
        auto& analogMap = m_keyMap.getMap(1); // id of controller

        if (analogMap.getValue(PIC.getAnalog(definitions::Action::MoveRight)) > 1) {
            move(delta, false);
        }
        if (analogMap.getValue(PIC.getAnalog(definitions::Action::MoveLeft)) < -1) {
            move(delta, true);
        }
        if (analogMap.hasKeyState(PIC.getKey(definitions::Action::MoveLeft), KeyStates::DOWN)) {
            move(delta, true);
        }
        if (analogMap.hasKeyState(PIC.getKey(definitions::Action::MoveRight), KeyStates::DOWN)) {
            move(delta, false);
        }
        if (analogMap.hasKeyState(PIC.getKey(definitions::Action::Jump), KeyStates::PRESSED)) {
            jump(delta);
        }

        if (delta != common::Vector2D<double>(0, 0)) {
            auto move = components::MoveComponent(delta);
            m_world.addComponent<components::MoveComponent>(entity, move);
        }
    });
}

void game::systems::PlayerInputSystem::move(common::Vector2D<double>& delta, bool invert)
{
    delta.x += invert ? -7 : 7;
}
void game::systems::PlayerInputSystem::jump(common::Vector2D<double>& delta)
{
    engine::sound::SDLSoundManager soundManager;
    engine::sound::SoundEffect sound("assets/sounds/jump.wav", 0);
    engine::sound::Volume volume { 10 };
    soundManager.setSfxVolume(volume);
    soundManager.play(sound);

    delta.y += 7;
}

void game::systems::PlayerInputSystem::render(engine::IRenderer& /* renderer */) {}
