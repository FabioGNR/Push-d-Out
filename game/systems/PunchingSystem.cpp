#include "PunchingSystem.h"
#include <chrono>
#include <engine/physics/DynamicBody.h>
#include <engine/sound/SoundEffect.h>
#include <functional>
#include <game/components/AnimationsComponent.h>
#include <game/components/BodyComponent.h>
#include <game/components/DimensionComponent.h>
#include <game/components/DirectionComponent.h>
#include <game/components/PlayerInputComponent.h>
#include <game/components/PositionComponent.h>
#include <game/components/SpriteComponent.h>
#include <game/definitions/Action.h>

namespace game::systems {
using namespace components;
void PunchingSystem::update(std::chrono::nanoseconds timeStep)
{
    using namespace std::chrono;

    m_ecsWorld->forEachEntityWith<PlayerInputComponent, PositionComponent, PunchComponent>([&](auto& entity) {
        auto& punchComponent = m_ecsWorld->getComponent<PunchComponent>(entity);
        if (!punchComponent.canPunch) {
            punchComponent.timeSincePunch += timeStep;
            double secondsSincePunch = duration_cast<milliseconds>(punchComponent.timeSincePunch).count() / 1000.0;
            if (secondsSincePunch > m_punchCooldownSeconds) {
                punchComponent.canPunch = true;
            }
        }
        if (punchComponent.canPunch && doesPlayerWantToPunch(entity)) {
            punch(entity, punchComponent);
        }
    });
}

void PunchingSystem::render(engine::IRenderer& /*renderer*/)
{
}

bool PunchingSystem::doesPlayerWantToPunch(const engine::ecs::Entity& player) const
{
    const auto& playerInputComponent = m_ecsWorld->getComponent<PlayerInputComponent>(player);
    const auto action = definitions::Action::Punch;
    const auto& control = playerInputComponent.getKey(action);
    const auto& analogControl = playerInputComponent.getAnalog(action);
    const auto& inputMap = m_inputMaps->getMap(playerInputComponent.controllerId);
    return inputMap.hasState(control, engine::input::States::PRESSED)
        || inputMap.hasState(analogControl, engine::input::States::PRESSED);
}

void PunchingSystem::punch(const engine::ecs::Entity& player, PunchComponent& punchComponent)
{
    playPunchAnimation(player);
    punchComponent.canPunch = false;
    punchComponent.timeSincePunch = std::chrono::nanoseconds(0);
    const auto* playerBody = m_ecsWorld->getComponent<BodyComponent>(player).body.get();
    const auto playerPosition = m_ecsWorld->getComponent<PositionComponent>(player).position;
    const auto playerDimension = m_ecsWorld->getComponent<DimensionComponent>(player).dimension;
    const auto punchRange = m_punchRange + (playerDimension.x / 2);
    const auto directionFactor = static_cast<int>(m_ecsWorld->getComponent<DirectionComponent>(player).direction);
    common::Vector2D<double> playerCenter = playerPosition + (playerDimension / 2);
    // try to punch horizontally
    common::Vector2D<double> horizontalRay = playerCenter + common::Vector2D<double>(directionFactor * punchRange, 0);
    common::Vector2D<double> upRay = playerCenter + common::Vector2D<double>(0, punchRange).rotateCounterClockwise(-directionFactor * 45);
    common::Vector2D<double> downRay = playerCenter + common::Vector2D<double>(0, -punchRange).rotateCounterClockwise(-directionFactor * 45);
    bool hasHit = attemptHitInDirection(playerBody, playerCenter, horizontalRay)
        || attemptHitInDirection(playerBody, playerCenter, upRay)
        || attemptHitInDirection(playerBody, playerCenter, downRay);
    if (hasHit) {
        engine::sound::SoundEffect sound("assets/sounds/punch.wav", 0);
        m_soundManager->play(sound);
    }
}

bool PunchingSystem::attemptHitInDirection(const engine::physics::Body* playerBody, const common::Vector2D<double>& from, const common::Vector2D<double>& to)
{
    engine::physics::RaycastHit closestHit{};
    bool hasHit{ false };
    auto raycastCallback
        = std::function<double(const engine::physics::RaycastHit& hit)>(
            [&](const auto& hit) {
                if (hit.body == playerBody) {
                    return -1.0; // ignore collisions with punching player
                }
                if (dynamic_cast<engine::physics::DynamicBody*>(hit.body) == nullptr) {
                    return -1.0; // ignore punching the floor or other static bodies
                }
                hasHit = true;
                closestHit = hit;
                return hit.fraction;
            });

    m_world->raycast(from, to, raycastCallback);
    if (!hasHit) {
        return false; // nothing to punch
    }
    const auto distanceVector = to - from;
    closestHit.body->applyLinearImpulse({ distanceVector.x * 20.0, distanceVector.y * 20.0 + 6.0 });
    return true;
}

void PunchingSystem::playPunchAnimation(const engine::ecs::Entity& player)
{
    auto& spriteComponent = m_ecsWorld->getComponent<components::SpriteComponent>(player);
    auto& animations = m_ecsWorld->getComponent<components::AnimationsComponent>(player).animations;
    const auto& punchAnimation = animations.find("Attacking");
    if (punchAnimation != animations.end()) {
        spriteComponent = punchAnimation->second;
        spriteComponent.loops = false;
    }
}
}