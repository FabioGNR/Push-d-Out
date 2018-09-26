#pragma once
#include "EventManager.h"
namespace engine {
class SDLEventManager : public EventManager {
public:
    bool processEvents() override;
};
}