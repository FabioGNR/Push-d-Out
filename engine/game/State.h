#pragma once

#include <chrono>
#include <graphics/IRenderer.h>

namespace engine {
class IGame;
class State {
protected:
    IGame& m_context;

public:
    explicit State(IGame& game) : m_context{game} {};
    virtual ~State() = default;

    virtual void init() = 0;
    virtual void update(std::chrono::nanoseconds timeStep) = 0;
    virtual void render(IRenderer& renderer) = 0;
};
}
