#pragma once

#include <game/State.h>

namespace game {
class MainMenuState : public engine::State {
public:
    void update(std::chrono::nanoseconds timeStep) override;
    void render(engine::IRenderer& renderer) override;
};
}
