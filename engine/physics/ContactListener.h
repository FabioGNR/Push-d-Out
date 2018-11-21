#pragma once

#include "Contact.h"
namespace engine {
namespace physics {
    class ContactListener {
    public:
        virtual void beginContact(Contact contact) = 0;
        virtual void endContact(Contact contact) = 0;
    };
}
}
