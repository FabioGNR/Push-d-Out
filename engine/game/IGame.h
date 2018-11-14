#pragma once

#include <chrono>
#include <iostream>
#include <memory>
#include <stack>

namespace engine {
class State;
class IGame {
private:
    bool m_isRunning = false;

protected:
    std::stack<std::unique_ptr<State>> m_states;

public:
    IGame() = default;
    IGame(const IGame& other) = default;
    IGame& operator=(const IGame& other) = default;

    IGame(IGame&& other) = default;
    IGame& operator=(IGame&& other) = default;
    virtual ~IGame() = default;

    virtual void init() = 0;
    virtual void onUpdate(std::chrono::nanoseconds timeStep) = 0;
    virtual void onRender() = 0;

    virtual void previous();
    virtual void next(std::unique_ptr<engine::State> state);
    virtual void stop();
    virtual void run();
};
}
