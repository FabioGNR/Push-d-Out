#pragma once

#include <engine/game/State.h>
#include <engine/ui/UISystem.h>

#include <memory>

namespace game {
class LevelSelectorState : public engine::State {
    std::vector<std::string> m_availableLevels;
    std::unique_ptr<engine::ui::UISystem> m_uiSystem;
    common::Vector2D<int> m_screenSize;

public:
    explicit LevelSelectorState(engine::IGame& context);
    ~LevelSelectorState() override = default;

    void update(std::chrono::nanoseconds timeStep) override;
    void render(engine::IRenderer& renderer) override;
    void init() override;
    void resume() override;
    void pause() override;
    void close() override;
};
}