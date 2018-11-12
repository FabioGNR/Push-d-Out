#pragma once

#include <engine/graphics/IRenderer.h>

#include <chrono>

namespace engine {
class State {
public:
    State() = default;
    State(const State& other) = default;
    State& operator=(const State& other) = default;

    State(State&& other) = default;
    State& operator=(State&& other) = default;
    virtual ~State() = default;

    virtual void update(std::chrono::nanoseconds timeStep) = 0;
    virtual void render(IRenderer& renderer) = 0;
    virtual void init(){};
    virtual void resume(){};
    virtual void pause(){};
    virtual void close(){};
};
}
