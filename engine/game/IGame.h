#pragma once

#include <chrono>
#include <iostream>

using namespace std::chrono_literals;

namespace engine {
class IGame {
private:
    bool m_isRunning = false;

public:
    IGame() = default;
    virtual ~IGame() = default;

    virtual void onInit() = 0;
    virtual void onUpdate(std::chrono::nanoseconds timeStep) = 0;
    virtual void onRender() = 0;

    virtual void stop()
    {
        m_isRunning = false;
    }

    virtual void run()
    {
        m_isRunning = true;

        onInit();
        using clock = std::chrono::steady_clock;

        const std::chrono::nanoseconds TIME_PER_UPDATE(2ms);
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
};
}
