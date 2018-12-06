#include "PlayerInputSystem.h"

#include <engine/sound/Music.h>
#include <engine/sound/SDL/SDLSoundManager.h>
#include <game/components/DirectionComponent.h>
#include <game/components/JumpComponent.h>
#include <game/components/LevelMetaComponent.h>
#include <game/components/MoveComponent.h>
#include <game/components/PlayerInputComponent.h>

using namespace game::components;

void game::systems::PlayerInputSystem::update(std::chrono::nanoseconds /* timeStep */)
{
    m_world.forEachEntityWith<PlayerInputComponent>([&](engine::ecs::Entity& entity) {
        auto& PIC = m_world.getComponent<PlayerInputComponent>(entity);
        auto& dirComp = m_world.getComponent<DirectionComponent>(entity);
        auto delta = common::Vector2D<double>(0, 0);
        auto& analogMap = m_inputMaps.getMap(PIC.controllerId); // id of controller

        if (analogMap.getValue(PIC.getAnalog(definitions::Action::MoveRight)) > moveDeadZone
            || analogMap.hasState(PIC.getKey(definitions::Action::MoveRight), engine::input::States::DOWN)) {
            move(delta, false, dirComp);
        } else if (analogMap.getValue(PIC.getAnalog(definitions::Action::MoveLeft)) < -moveDeadZone
            || analogMap.hasState(PIC.getKey(definitions::Action::MoveLeft), engine::input::States::DOWN)) {
            move(delta, true, dirComp);
        }
        if (delta != common::Vector2D<double>(0, 0)) {
            auto move = components::MoveComponent(delta);
            m_world.addComponent<MoveComponent>(entity, move);
        }
    });

    m_world.forEachEntityWith<PlayerInputComponent, JumpComponent>([&](engine::ecs::Entity& entity) {
        auto& jumpComp = m_world.getComponent<JumpComponent>(entity);

        if (!jumpComp.mayJump) {
            return; // if it may not jump
        }

        auto& PIC = m_world.getComponent<components::PlayerInputComponent>(entity);
        auto& analogMap = m_inputMaps.getMap(PIC.controllerId); // id of controller

        auto delta = common::Vector2D<double>(0, 0);

        if (analogMap.hasState(PIC.getKey(definitions::Action::Jump), engine::input::States::PRESSED)) {
            jump(delta);
        }

        if (delta != common::Vector2D<double>(0, 0)) {
            jumpComp.delta = delta;
            jumpComp.mayJump = false; // disable jump till it hits the ground
        }
    });
}

void game::systems::PlayerInputSystem::move(common::Vector2D<double>& delta, bool invert, components::DirectionComponent& directionComponent)
{
    auto levelIt = m_world.begin<LevelMetaComponent>();
    LevelMetaComponent* level = nullptr;
    if (levelIt != m_world.end<LevelMetaComponent>()) {
        level = dynamic_cast<LevelMetaComponent*>(levelIt->second.get());
    }

    auto deltaX = level != nullptr ? level->theme.movementSpeed : 20;
    delta.x += invert ? -deltaX : deltaX;
    directionComponent.direction = (invert) ? DirectionComponent::Direction::LEFT : DirectionComponent::Direction::RIGHT;
}
void game::systems::PlayerInputSystem::jump(common::Vector2D<double>& delta)
{
    auto levelIt = m_world.begin<LevelMetaComponent>();
    LevelMetaComponent* level = nullptr;
    if (levelIt != m_world.end<LevelMetaComponent>()) {
        level = dynamic_cast<LevelMetaComponent*>(levelIt->second.get());
    }

    engine::sound::SoundEffect sound("assets/sounds/jump.wav", 0);
    engine::sound::Volume volume{ 10 };
    m_soundManager->setSfxVolume(volume);
    m_soundManager->play(sound);

    delta.y += level != nullptr ? level->theme.jumpSpeed : 10;
}

void game::systems::PlayerInputSystem::render(engine::IRenderer& /* renderer */) {}
