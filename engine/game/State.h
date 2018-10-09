#pragma once

#include <chrono>
#include <graphics/IRenderer.h>

namespace engine {
class State {
private:
public:
    State() = default;
    virtual ~State() = default;

    virtual void update(std::chrono::nanoseconds timeStep) = 0;
    virtual void render(IRenderer &renderer) = 0;
};
}
