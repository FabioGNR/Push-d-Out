#pragma once

#include <chrono>
#include <iostream>
#include <stack>
#include <memory>

using namespace std::chrono_literals;

namespace engine {
class State;
class IGame {
private:
    bool m_isRunning = false;

protected:
    std::stack<std::shared_ptr<State>> m_states;

public:
    IGame() = default;
    virtual ~IGame() = default;

    virtual void init() = 0;
    virtual void onUpdate(std::chrono::nanoseconds timeStep) = 0;
    virtual void onRender() = 0;

    virtual void previous();
    virtual void next(std::shared_ptr<engine::State> state);
    virtual void stop();
    virtual void run();
};
}
