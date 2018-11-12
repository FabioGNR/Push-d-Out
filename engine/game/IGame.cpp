#include "IGame.h"
#include "State.h"


using namespace std::chrono_literals;

namespace engine {
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

void IGame::next(const std::shared_ptr<engine::State>& state)
{
    if (!m_states.empty()) {
        auto& currentState = m_states.top();
        currentState->pause();
    }
    m_states.push(state);
    state->init();
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
            onUpdate(TIME_PER_UPDATE);
        }

        // how far we are into the frame
        onRender();
    }
}
} // end namespace engine