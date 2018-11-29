#include "PlayerInputSystem.h"

#include <engine/sound/Music.h>
#include <engine/sound/SDL/SDLSoundManager.h>
#include <game/components/DirectionComponent.h>
#include <game/components/JumpComponent.h>
#include <game/components/LevelMetaComponent.h>
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

        if (analogMap.getValue(PIC.getAnalog(definitions::Action::MoveRight)) > moveDeadZone) {
            move(delta, false, dirComp);
        } else if (analogMap.getValue(PIC.getAnalog(definitions::Action::MoveLeft)) < -moveDeadZone) {
            move(delta, true, dirComp);
        } else if (analogMap.hasState(PIC.getKey(definitions::Action::MoveLeft), States::DOWN)) {
            move(delta, true, dirComp);
        } else if (analogMap.hasState(PIC.getKey(definitions::Action::MoveRight), States::DOWN)) {
            move(delta, false, dirComp);
        }
        //if (analogMap.hasState(PIC.getKey(definitions::Action::Jump), States::PRESSED)) {

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

        if (analogMap.hasState(PIC.getKey(definitions::Action::Jump), States::PRESSED)) {
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
    auto levelIt = m_world.begin<components::LevelMetaComponent>();
    components::LevelMetaComponent* level = nullptr;
    if (levelIt != m_world.end<components::LevelMetaComponent>()) {
        level = dynamic_cast<components::LevelMetaComponent*>(levelIt->second.get());
    }

    auto deltaX = level != nullptr ? level->theme.movementSpeed : 20;
    delta.x += invert ? -deltaX : deltaX;
    directionComponent.setDir(!invert);
}
void game::systems::PlayerInputSystem::jump(common::Vector2D<double>& delta)
{
    auto levelIt = m_world.begin<components::LevelMetaComponent>();
    components::LevelMetaComponent* level = nullptr;
    if (levelIt != m_world.end<components::LevelMetaComponent>()) {
        level = dynamic_cast<components::LevelMetaComponent*>(levelIt->second.get());
    }

    engine::sound::SoundEffect sound("assets/sounds/jump.wav", 0);
    engine::sound::Volume volume{ 10 };
    m_soundManager->setSfxVolume(volume);
    m_soundManager->play(sound);

    delta.y += level != nullptr ? level->theme.jumpSpeed : 10;
}

void game::systems::PlayerInputSystem::render(engine::IRenderer& /* renderer */) {}
