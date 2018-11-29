#include "JumpContactListener.h"
#include <game/components/JumpComponent.h>
#include <game/components/PlayerInputComponent.h>

namespace game {
namespace listeners {
    void JumpContactListener::beginContact(engine::physics::Contact contact)
    {
        auto& a = m_world->getEntity(contact.a->getEntityId());
        auto& b = m_world->getEntity(contact.b->getEntityId());

        if (a.hasComponent<components::PlayerInputComponent, components::JumpComponent>()
            && !b.hasComponent<components::PlayerInputComponent>()) {
            resetJump(a);
        } else if (!a.hasComponent<components::PlayerInputComponent>()
            && b.hasComponent<components::PlayerInputComponent, components::JumpComponent>()) {
            resetJump(b);
        }
    }

    void JumpContactListener::resetJump(engine::ecs::Entity& e)
    {
        auto& jump = m_world->getComponent<components::JumpComponent>(e);
        jump.mayJump = true;
    }

    void JumpContactListener::endContact(engine::physics::Contact /* contact */)
    {
    }
}
}
