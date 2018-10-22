#pragma once

#include <events/models/IEvent.h>
#include <memory>

namespace engine {
namespace events {
    class IEventHandler {
    private:
    public:
        virtual ~IEventHandler() = default;
        virtual std::vector<std::shared_ptr<IEvent>> getEvents() = 0;
    };
}
}
