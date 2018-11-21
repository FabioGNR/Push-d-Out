#pragma once

#include "Body.h"

namespace engine {
namespace physics {
    struct Contact {
        Contact(Body* body1, Body* body2)
            : a{ body1 }
            , b{ body2 }
        {
        }

        Body* a;
        Body* b;
    };
}
}
