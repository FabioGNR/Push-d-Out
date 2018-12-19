#include "ProjectileContactListener.h"
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

    void ProjectileContactListener::beginContact(engine::physics::Contact contact)
    {
        try {
            auto& a = m_ecsWorld->getEntity(contact.a->getEntityId());
            auto& b = m_ecsWorld->getEntity(contact.b->getEntityId());

            if (a.hasComponent<components::ProjectileComponent>()
                && !b.hasComponent<components::PortalComponent>()
                && b.hasComponent<components::BodyComponent>()) {
                act(a, b, m_ecsWorld->getComponent<components::PositionComponent>(a).position);
            } else if (a.hasComponent<components::BodyComponent>()
                && !a.hasComponent<components::PortalComponent>()
                && b.hasComponent<components::ProjectileComponent>()) {
                act(b, a, m_ecsWorld->getComponent<components::PositionComponent>(b).position);
            }
        } catch (engine::exceptions::EntityNotFoundException&) {
            return; // nothing to do here
        }
    }

    void ProjectileContactListener::act(engine::ecs::Entity& projectile, engine::ecs::Entity& body, common::Vector2D<double> position)
    {
        auto& proj = m_ecsWorld->getComponent<components::ProjectileComponent>(projectile);
        switch (proj.type) {
        case definitions::ProjectileType::Force:
            applyForce(body, projectile);
            break;
        case definitions::ProjectileType::BluePortal:
            createPortal(position, false);
            break;
        case definitions::ProjectileType::OrangePortal:
            createPortal(position, true);
            break;
        case definitions::ProjectileType::None:
            break;
        }

        m_ecsWorld->destroyEntityNextUpdate(projectile);
    }

    void ProjectileContactListener::endContact(engine::physics::Contact /* contact */)
    {
    }

    void ProjectileContactListener::createPortal(common::Vector2D<double> position, bool alternative)
    {
        position.y += 1;
        auto* entity = findPortal(alternative);
        if (entity != nullptr) {
            auto& pos = m_ecsWorld->getComponent<components::PositionComponent>(*entity);
            auto& body = *m_ecsWorld->getComponent<components::BodyComponent>(*entity).body;

            pos.position = position;
            body.setPosition(position);
        } else {
            common::Vector2D<double> dimensions(1, 2);

            auto& portal = m_ecsWorld->createEntity();
            auto body = m_physicsWorld->createStaticBody(position, common::Vector2D<double>(.1, 2), portal.id());
            body->setGravityScale(2);
            body->setSensor(true);

            auto posComponent = components::PositionComponent(position);
            m_ecsWorld->addComponent<components::PositionComponent>(portal, posComponent);

            auto bodyComponent = components::BodyComponent(std::move(body));
            m_ecsWorld->addComponent<components::BodyComponent>(portal, std::move(bodyComponent));

            auto dimensionComponent = components::DimensionComponent(dimensions);
            m_ecsWorld->addComponent<components::DimensionComponent>(portal, dimensionComponent);

            auto portalComponent = components::PortalComponent(!alternative);
            m_ecsWorld->addComponent<components::PortalComponent>(portal, portalComponent);

            game::builders::SpriteBuilder builder{
                "assets/sprites/equipment/equipment.png",
                "assets/sprites/equipment/equipment.json"
            };
            auto sprites = builder.build();
            auto sprite = alternative ? sprites.find("Portal-1") : sprites.find("Portal-0");
            if (sprite != sprites.end()) {
                m_ecsWorld->addComponent<components::SpriteComponent>(portal, sprite->second);
            }
        }
    }

    engine::ecs::Entity* ProjectileContactListener::findPortal(bool alternative)
    {
        engine::ecs::Entity* entity = nullptr;

        m_ecsWorld->forEachEntityWith<components::PortalComponent, components::PositionComponent, components::BodyComponent>(
            [&](engine::ecs::Entity& e) {
                auto portal = m_ecsWorld->getComponent<components::PortalComponent>(e);
                if (portal.isPrimary != alternative) {
                    entity = &e;
                }
            });

        return entity;
    }

    void ProjectileContactListener::applyForce(engine::ecs::Entity& body, engine::ecs::Entity& projectile)
    {
        auto& player = m_ecsWorld->getComponent<components::BodyComponent>(body).body;
        auto force = m_ecsWorld->getComponent<components::ProjectileComponent>(projectile).force;
        player->applyLinearImpulse(force * 40);
    }
}
}
