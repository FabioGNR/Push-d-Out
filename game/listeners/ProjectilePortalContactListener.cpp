#include "ProjectilePortalContactListener.h"
#include "game/components/PositionComponent.h"
#include "game/components/ProjectileComponent.h"
#include <engine/exceptions/EntityNotFoundException.h>
#include <game/builders/SpriteBuilder.h>
#include <game/components/BodyComponent.h>
#include <game/components/DimensionComponent.h>
#include <game/components/PortalComponent.h>
#include <game/components/PositionComponent.h>

namespace game {
namespace listeners {

    void ProjectilePortalContactListener::beginContact(engine::physics::Contact& contact)
    {
        try {
            auto& a = m_ecsWorld->getEntity(contact.a->getEntityId());
            auto& b = m_ecsWorld->getEntity(contact.b->getEntityId());

            if (a.hasComponent<components::ProjectileComponent>()
                && b.hasComponent<components::PortalComponent>()) {
                teleportProjectile(a, b);
            } else if (a.hasComponent<components::PortalComponent>()
                && b.hasComponent<components::ProjectileComponent>()) {
                teleportProjectile(b, a);
            }
        } catch (engine::exceptions::EntityNotFoundException&) {
            return; // nothing to do here
        }
    }

    void ProjectilePortalContactListener::teleportProjectile(engine::ecs::Entity& projectile,
        engine::ecs::Entity& portal)
    {
        auto* other = findOtherPortal(portal.id());

        if (other != nullptr) {
            auto pos1 = m_ecsWorld->getComponent<components::PositionComponent>(portal).position;
            auto pos2 = m_ecsWorld->getComponent<components::PositionComponent>(*other).position;

            auto delta = pos2 - pos1;
            auto vel = m_ecsWorld->getComponent<components::BodyComponent>(projectile).body->getLinearVelocity();
            auto direction = vel.normalize();
            m_projectilesToUpdate[projectile.id()] = m_ecsWorld->getComponent<components::PositionComponent>(projectile).position + delta + direction;
        }
    }

    void ProjectilePortalContactListener::endContact(engine::physics::Contact& /* contact */)
    {
    }

    engine::ecs::Entity* ProjectilePortalContactListener::findOtherPortal(engine::ecs::EntityId id)
    {
        engine::ecs::Entity* entity = nullptr;

        m_ecsWorld->forEachEntityWith<components::PortalComponent,
            components::PositionComponent,
            components::BodyComponent>(
            [&](engine::ecs::Entity& e) {
                if (e.id() != id) {
                    entity = &e;
                }
            });

        return entity;
    }

    void ProjectilePortalContactListener::preSolve(engine::physics::Contact& /* contact */)
    {
    }

    void ProjectilePortalContactListener::postSolve(engine::physics::Contact& /* contact */)
    {
    }

    void ProjectilePortalContactListener::update(std::chrono::nanoseconds /* dt */)
    {
        std::for_each(m_projectilesToUpdate.begin(), m_projectilesToUpdate.end(), [&](auto& entity) {
            auto& body = m_ecsWorld->getComponent<components::BodyComponent>(m_ecsWorld->getEntity(entity.first)).body;
            body->setPosition(entity.second);
        });

        m_projectilesToUpdate.clear();
    }
}
}
