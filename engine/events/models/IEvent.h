#pragma once

#include <iostream>
#include <vector>

namespace engine {
namespace events {
    struct IEvent {
        virtual ~IEvent() = default;
    };
}
}
