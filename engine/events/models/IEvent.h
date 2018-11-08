#pragma once

#include <iostream>
#include <vector>

namespace engine {
namespace events {
    struct IEvent {
        IEvent() = default;
        IEvent(const IEvent& other) = default;
        IEvent& operator=(const IEvent& other) = default;

        IEvent(IEvent&& other) = default;
        IEvent& operator=(IEvent&& other) = default;
        virtual ~IEvent() = default;
    };
}
}
