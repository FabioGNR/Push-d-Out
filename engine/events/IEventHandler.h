#pragma once

#include <engine/events/models/IEvent.h>
#include <memory>

namespace engine {
namespace events {
    class IEventHandler {
    private:
    public:
        IEventHandler() = default;
        IEventHandler(const IEventHandler& other) = default;
        IEventHandler& operator=(const IEventHandler& other) = default;

        IEventHandler(IEventHandler&& other) = default;
        IEventHandler& operator=(IEventHandler&& other) = default;
        virtual ~IEventHandler() = default;
        virtual std::vector<std::unique_ptr<IEvent>> getEvents() = 0;
        virtual size_t getConnectedControllers() = 0;
    };
}
}
