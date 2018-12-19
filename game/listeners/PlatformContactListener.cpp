#include "PlatformContactListener.h"
#include <game/components/BodyComponent.h>
#include <game/components/JumpComponent.h>
#include <game/components/PlayerInputComponent.h>
#include <game/components/PositionComponent.h>
#include <game/components/TileComponent.h>

namespace game {
namespace listeners {
    void PlatformContactListener::beginContact(engine::physics::Contact& /* contact */)
    {
    }

    void PlatformContactListener::endContact(engine::physics::Contact& /* contact */)
    {
    }

    void PlatformContactListener::preSolve(engine::physics::Contact& contact)
    {
        try {
            auto& a = m_world->getEntity(contact.a->getEntityId());
            auto& b = m_world->getEntity(contact.b->getEntityId());

            if (a.hasComponent<components::PlayerInputComponent>()
                && b.hasComponent<components::TileComponent>()) {
                disableContact(contact, a, b);
            } else if (a.hasComponent<components::TileComponent>()
                && b.hasComponent<components::PlayerInputComponent>()) {
                disableContact(contact, b, a);
            }
        } catch (...) {
            return; // nothing to do here!
        }
    }

    void PlatformContactListener::postSolve(engine::physics::Contact& /* contact */)
    {
    }

    void PlatformContactListener::disableContact(engine::physics::Contact& contact,
        engine::ecs::Entity& player,
        engine::ecs::Entity& tile)
    {
        auto& tilePosition = m_world->getComponent<components::PositionComponent>(tile).position;
        auto& playerPosition = m_world->getComponent<components::PositionComponent>(player).position;
        auto input = m_world->getComponent<components::PlayerInputComponent>(player);

        auto keyState = m_inputMaps->getMap(input.controllerId).getState(input.getKey(definitions::Action::Jump));
        if (playerPosition.y < tilePosition.y && keyState == engine::input::States::DOWN) {
            contact.setEnabled(false);
        }
    }
}
}
