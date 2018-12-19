#include "ProjectileContactListener.h"
#include "game/components/PositionComponent.h"
#include "game/components/ProjectileComponent.h"
#include <engine/exceptions/EntityNotFoundException.h>
#include <game/builders/SpriteBuilder.h>
#include <game/components/BodyComponent.h>
#include <game/components/DimensionComponent.h>
#include <game/components/PlayerInputComponent.h>
#include <game/components/PortalComponent.h>
#include <game/components/PositionComponent.h>
#include <game/components/VisualEffectComponent.h>
#include <game/systems/VisualEffectSystem.h>
#include <set>

namespace game {
namespace listeners {

    void ProjectileContactListener::beginContact(engine::physics::Contact& contact)
    {
        try {
            auto& a = m_ecsWorld->getEntity(contact.a->getEntityId());
            auto& b = m_ecsWorld->getEntity(contact.b->getEntityId());

            if (a.hasComponent<components::ProjectileComponent>()
                && !b.hasComponent<components::PortalComponent>()
                && b.hasComponent<components::BodyComponent>()) {
                auto& projectilePos = m_ecsWorld->getComponent<components::PositionComponent>(a).position;
                auto& projectileDim = m_ecsWorld->getComponent<components::DimensionComponent>(a).dimension;
                auto& projectileComponent = m_ecsWorld->getComponent<components::ProjectileComponent>(a);
                auto& bodyComponent = m_ecsWorld->getComponent<components::BodyComponent>(a);
                ProjectileContactData projCont{projectilePos, projectileDim, contact.normal, bodyComponent.body->getLinearVelocity(), projectileComponent.type};
                m_ecsWorld->destroyEntityNextUpdate(a);
                act(projCont, b);
            } else if (a.hasComponent<components::BodyComponent>()
                && !a.hasComponent<components::PortalComponent>()
                && b.hasComponent<components::ProjectileComponent>()) {
                auto& projectilePos = m_ecsWorld->getComponent<components::PositionComponent>(b).position;
                auto& projectileDim = m_ecsWorld->getComponent<components::DimensionComponent>(b).dimension;
                auto& projectileComponent = m_ecsWorld->getComponent<components::ProjectileComponent>(b);
                auto& bodyComponent = m_ecsWorld->getComponent<components::BodyComponent>(b);
                ProjectileContactData projCont{projectilePos, projectileDim, contact.normal, bodyComponent.body->getLinearVelocity(), projectileComponent.type};
                m_ecsWorld->destroyEntityNextUpdate(b);
                act(projCont, a);
            }
        } catch (engine::exceptions::EntityNotFoundException&) {
            return; // nothing to do here
        }
    }

    void ProjectileContactListener::act(ProjectileContactData projectile, engine::ecs::Entity& body)
    {

        if (body.hasComponent<components::PlayerInputComponent>()) {
            applyForce(body, projectile);
        }

        switch (projectile.type) {
        case definitions::ProjectileType::Grenade:
            explode(projectile, GRENADE_RADIUS);
            break;
        case definitions::ProjectileType::Force:
            applyForce(body, projectile);
            break;
        case definitions::ProjectileType::BluePortal:
            createPortalNextUpdate(projectile, false);
            break;
        case definitions::ProjectileType::OrangePortal:
            createPortalNextUpdate(projectile, true);
            break;
        case definitions::ProjectileType::None:
            break;
        }
    }

    void ProjectileContactListener::createPortalNextUpdate(ProjectileContactData projectile, bool alternative)
    {

        PortalBlueprint bp {};
        bp.container = projectile;
        bp.isAlternative = alternative;
        m_portalsToBuild.push_back(bp);
    }

    void ProjectileContactListener::endContact(engine::physics::Contact& /* contact */)
    {
    }

    void ProjectileContactListener::createPortal(ProjectileContactData projectile, bool alternative)
    {
        projectile.position += projectile.contactNormal;

        auto* entity = findPortal(alternative);
        if (entity != nullptr) {
            auto& pos = m_ecsWorld->getComponent<components::PositionComponent>(*entity);
            auto& body = *m_ecsWorld->getComponent<components::BodyComponent>(*entity).body;

            pos.position = projectile.position;
            body.setPosition(projectile.position);
        } else {
            common::Vector2D<double> dimensions(1, 2);

            auto& portal = m_ecsWorld->createEntity();
            auto body = m_physicsWorld->createStaticBody(projectile.position, common::Vector2D<double>(.1, 2), portal.id());
            body->setSensor(true);

            auto posComponent = components::PositionComponent(projectile.position);
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

    void ProjectileContactListener::applyForce(engine::ecs::Entity& body, ProjectileContactData projectile)
    {
        auto& player = m_ecsWorld->getComponent<components::BodyComponent>(body).body;
        player->applyLinearImpulse(projectile.direction.normalize() * 25);
    }

    void ProjectileContactListener::explode(ProjectileContactData projectile, double radius)
    {
        int amountOfRays = 100;
        double degrees = 360.0 / amountOfRays;
        engine::physics::RaycastHit closestHit{};
        std::set<engine::physics::Body*> pushedBodies;

        bool hasHit { false };
        const auto& projectileCenter = projectile.position + projectile.dimension / 2;

        engine::physics::RaycastCallback callback = [&](engine::physics::RaycastHit hit) {
            closestHit = hit;
            hasHit = true;
            return hit.fraction;
        };

        common::Vector2D<double> toBase{ 0, radius };

        for (int i = 0; i < amountOfRays; i++) {
            common::Vector2D<double> toVector = toBase.rotateCounterClockwise(i * degrees);
            m_physicsWorld->raycast(projectileCenter, projectileCenter + toVector, callback);
            if (hasHit && pushedBodies.find(closestHit.body) == pushedBodies.end()) {
                common::Vector2D bodyPos = closestHit.body->getPosition() + closestHit.body->getDimensions() / 2;
                auto impulseVector = bodyPos - projectileCenter;
                closestHit.body->applyLinearImpulse(impulseVector * std::max(0.0, (radius - impulseVector.magnitude()) * 5));
                pushedBodies.insert(closestHit.body); // prevent pushing a body more than once
            }
            hasHit = false; // reset hit for next ray
        }

        builders::SpriteBuilder spriteBuilder{ "assets/sprites/particles/particles.png", "assets/sprites/particles/particles.json" };
        auto spriteComponents = spriteBuilder.build();
        auto spriteComponentPair = spriteComponents.find("ForceExplosion");
        if (spriteComponentPair != spriteComponents.end()) {
            auto& spriteEntity = m_ecsWorld->createEntity();
            auto spriteComponent = spriteComponentPair->second;
            spriteComponent.loops = false;
            m_ecsWorld->addComponent<components::SpriteComponent>(spriteEntity, spriteComponent);
            auto visualEffectComponent = components::VisualEffectComponent{};
            m_ecsWorld->addComponent<components::VisualEffectComponent>(spriteEntity);
            auto posComponent = components::PositionComponent{ projectileCenter - radius };
            m_ecsWorld->addComponent<components::PositionComponent>(spriteEntity, posComponent);
            auto dimComponent = components::DimensionComponent{ { radius * 2, radius * 2 } };
            m_ecsWorld->addComponent<components::DimensionComponent>(spriteEntity, dimComponent);
        }
    }

    void ProjectileContactListener::preSolve(engine::physics::Contact& /* contact */)
    {
    }

    void ProjectileContactListener::postSolve(engine::physics::Contact& /* contact */)
    {
    }

    void ProjectileContactListener::update(std::chrono::nanoseconds /* nanoseconds */)
    {
        for (auto& portal : m_portalsToBuild) {
            createPortal(portal.container, portal.isAlternative);
        }
        m_portalsToBuild.clear();
    }
}
}
