#include "PortalContactListener.h"
#include <engine/exceptions/EntityNotFoundException.h>
#include <game/components/BodyComponent.h>
#include <game/components/PlayerInputComponent.h>
#include <game/components/PositionComponent.h>
#include <game/components/ProjectileComponent.h>
#include <game/components/TeleportComponent.h>

namespace game::listeners {
void PortalContactListener::beginContact(engine::physics::Contact contact)
{
    try {
        auto& a = m_ecsWorld->getEntity(contact.a->getEntityId());
        auto& b = m_ecsWorld->getEntity(contact.b->getEntityId());

        if (a.hasComponent<components::PortalComponent>()
            && b.hasComponent<components::PlayerInputComponent>()) {
            teleport(a, b);
        } else if (a.hasComponent<components::PlayerInputComponent>()
            && b.hasComponent<components::PortalComponent>()) {
            teleport(b, a);
        }
    } catch (engine::exceptions::EntityNotFoundException&) {
        return; // nothing to do here
    }
}

void PortalContactListener::teleport(engine::ecs::Entity& portal, engine::ecs::Entity& player)
{
    auto endpoint = findOtherPortal(portal.id());
    if (endpoint == nullptr) {
        return;
    }

    // add teleport component to player
    auto& pos = m_ecsWorld->getComponent<components::PositionComponent>(*endpoint);

    // get existing teleportComponent
    bool hasTp = player.hasComponent<components::TeleportComponent>();
    if (hasTp) {
        auto& tp = m_ecsWorld->getComponent<components::TeleportComponent>(player);
        tp.position = pos.position;
        tp.inRange = true;
    } else {
        components::TeleportComponent tp{ pos.position };
        m_ecsWorld->addComponent<components::TeleportComponent>(player, tp);
    }
}

void PortalContactListener::endContact(engine::physics::Contact contact)
{
    try {
        auto& a = m_ecsWorld->getEntity(contact.a->getEntityId());
        auto& b = m_ecsWorld->getEntity(contact.b->getEntityId());

        if (a.hasComponent<components::PortalComponent>()
            && b.hasComponent<components::TeleportComponent>()) {
            reset(b);
        } else if (a.hasComponent<components::TeleportComponent>()
            && b.hasComponent<components::PortalComponent>()) {
            reset(a);
        }
    } catch (engine::exceptions::EntityNotFoundException&) {
        return; // nothing to do here
    }
}

void PortalContactListener::reset(engine::ecs::Entity& player)
{
    auto& tp = m_ecsWorld->getComponent<components::TeleportComponent>(player);
    tp.enabled = true;
    tp.inRange = false;
    tp.timeout = components::TeleportComponent::COOLDOWN;
}

engine::ecs::Entity* PortalContactListener::findOtherPortal(engine::ecs::EntityId id)
{
    engine::ecs::Entity* entity = nullptr;

    m_ecsWorld->forEachEntityWith<components::PortalComponent, components::PositionComponent, components::BodyComponent>(
        [&](engine::ecs::Entity& e) {
            if (e.id() != id) {
                entity = &e;
            }
        });

    return entity;
}
}
