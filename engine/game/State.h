#pragma once

#include <engine/graphics/IRenderer.h>

#include <chrono>

namespace engine {
class IGame;
class State {
protected:
    IGame& m_context;

public:
    explicit State(IGame& game)
        : m_context{ game } {};

    State(const State& other) = delete;
    State& operator=(const State& other) = delete;

    State(State&& other) = delete;
    State& operator=(State&& other) = delete;
    virtual ~State() = default;

    virtual void update(std::chrono::nanoseconds timeStep) = 0;
    virtual void render(IRenderer& renderer) = 0;
    virtual void init(){};
    virtual void resume(){};
    virtual void pause(){};
    virtual void close(){};
};
}
