#pragma once

#include "Body.h"
#include "Contact.h"

class b2Contact;

namespace engine {
namespace physics {
    class ContactImpl : public Contact {
    private:
        b2Contact* m_contact;

    public:
        explicit ContactImpl(b2Contact* contact)
            : m_contact{ contact } {};

        void setEnabled(bool enabled) override;
    };
}
}
