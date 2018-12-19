#include "IGame.h"
#include "State.h"

namespace engine {

using namespace std::chrono_literals;

void IGame::previous()
{
    if (!m_states.empty()) {
        auto& currentState = m_states.top();
        currentState->close();
    }
    m_states.pop();
    if (m_states.empty()) {
        stop();
    } else {
        auto& newState = m_states.top();
        newState->resume();
    }
}

void IGame::next(std::unique_ptr<engine::State> state)
{
    if (!m_states.empty()) {
        auto& currentState = m_states.top();
        currentState->pause();
    }
    auto* addedState = state.get();
    m_states.push(std::move(state));
    addedState->init();
}

void IGame::stop()
{
    m_isRunning = false;
}

void IGame::run()
{
    m_isRunning = true;

    using clock = std::chrono::steady_clock;

    const std::chrono::nanoseconds TIME_PER_UPDATE(16ms);
    std::chrono::nanoseconds lag(0ns);
    auto lastTime = clock::now();

    while (m_isRunning) {
        auto deltaTime = std::chrono::steady_clock::now() - lastTime; // time of one iteration
        lastTime = clock::now(); // reset

        lag += std::chrono::duration_cast<std::chrono::nanoseconds>(deltaTime);

        // update game logic as lag permits
        while (lag >= TIME_PER_UPDATE) {
            lag -= TIME_PER_UPDATE;
            auto updateDuration = std::chrono::duration<double, std::nano>(TIME_PER_UPDATE.count() * m_speed);
            onUpdate(std::chrono::duration_cast<std::chrono::nanoseconds>(updateDuration));
        }

        // how far we are into the frame
        onRender();
    }
}

void IGame::setSpeed(double speed)
{
    m_speed = speed;
}

void IGame::resetSpeed()
{
    m_speed = 1;
}

double IGame::speed() const
{
    return m_speed;
}

void IGame::clearStates()
{
    while (!m_states.empty()) {
        auto& currentState = m_states.top();
        currentState->close();
        m_states.pop();
    }
}

State* IGame::getPreviousStateByIndex(int index)
{
    if (m_states.empty() || m_states.size() == 1) {
        return nullptr;
    }
    auto currentState = std::find(m_states.begin(), m_states.end(), m_states.top());
    currentState -= index;
    return (*currentState).get();
}
}
