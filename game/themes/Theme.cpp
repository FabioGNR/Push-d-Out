#include "Theme.h"

namespace game {
namespace themes {
    double Theme::getGravity() const
    {
        return Theme::_gravity;
    }

    double Theme::getFriction() const
    {
        return Theme::_friction;
    }
}
}
