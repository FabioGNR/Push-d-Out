#pragma once
namespace engine {
class EventManager {
public:
    virtual bool processEvents() = 0;
    virtual ~EventManager() = default;
};
}