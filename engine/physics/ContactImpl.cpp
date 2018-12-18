#include "ContactImpl.h"
#include <Box2D/Dynamics/Contacts/b2Contact.h>

namespace engine::physics {
void ContactImpl::setEnabled(bool enabled)
{
    m_contact->SetEnabled(enabled);
}
}
