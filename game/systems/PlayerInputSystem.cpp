#include "PlayerInputSystem.h"

#include <engine/sound/Music.h>
#include <engine/sound/SDL/SDLSoundManager.h>
#include <game/components/DirectionComponent.h>
#include <game/components/JumpComponent.h>
#include <game/components/MoveComponent.h>
#include <game/components/PlayerInputComponent.h>

using namespace engine::input;

void game::systems::PlayerInputSystem::update(std::chrono::nanoseconds /* timeStep */)
{
    m_world.forEachEntityWith<components::PlayerInputComponent>([&](engine::ecs::Entity& entity) {
        auto& PIC = m_world.getComponent<components::PlayerInputComponent>(entity);
        auto& dirComp = m_world.getComponent<components::DirectionComponent>(entity);
        auto delta = common::Vector2D<double>(0, 0);
        auto& analogMap = m_inputMaps.getMap(PIC.controllerId); // id of controller

        if (analogMap.getValue(PIC.getAnalog(definitions::Action::MoveRight)) > 1) {
            move(delta, false, dirComp);
        }
        if (analogMap.getValue(PIC.getAnalog(definitions::Action::MoveLeft)) < -1) {
            move(delta, true, dirComp);
        }
        if (analogMap.hasKeyState(PIC.getKey(definitions::Action::MoveLeft), KeyStates::DOWN)) {
            move(delta, true, dirComp);
        }
        if (analogMap.hasKeyState(PIC.getKey(definitions::Action::MoveRight), KeyStates::DOWN)) {
            move(delta, false, dirComp);
        }

        if (delta != common::Vector2D<double>(0, 0)) {
            auto move = components::MoveComponent(delta);
            m_world.addComponent<components::MoveComponent>(entity, move);
        }
    });

    m_world.forEachEntityWith<components::PlayerInputComponent, components::JumpComponent>([&](engine::ecs::Entity& entity) {
        auto& jumpComp = m_world.getComponent<components::JumpComponent>(entity);

        if (!jumpComp.mayJump) {
            return; // if it may not jump
        }

        auto& PIC = m_world.getComponent<components::PlayerInputComponent>(entity);
        auto& analogMap = m_inputMaps.getMap(PIC.controllerId); // id of controller

        auto delta = common::Vector2D<double>(0, 0);

        if (analogMap.hasKeyState(PIC.getKey(definitions::Action::Jump), KeyStates::PRESSED)) {
            jump(delta);
        }

        if (delta != common::Vector2D<double>(0, 0)) {
            jumpComp.delta = delta;
            jumpComp.mayJump = false; // disable jump till it hits the ground
        }
    });
}

void game::systems::PlayerInputSystem::move(common::Vector2D<double>& delta, bool invert, game::components::DirectionComponent& directionComponent)
{
    delta.x += invert ? -20 : 20; // magix value was 7
    directionComponent.setDir(!invert);
}
void game::systems::PlayerInputSystem::jump(common::Vector2D<double>& delta)
{

    engine::sound::SoundEffect sound("assets/sounds/jump.wav", 0);
    engine::sound::Volume volume{ 10 };
    m_soundManager->setSfxVolume(volume);
    m_soundManager->play(sound);

    delta.y += 10;
}

void game::systems::PlayerInputSystem::render(engine::IRenderer& /* renderer */) {}
