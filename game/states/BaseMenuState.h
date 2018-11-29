#pragma once

#include <chrono>
#include <engine/events/models/Subscription.h>
#include <engine/game/State.h>
#include <engine/ui/UISystem.h>
#include <engine/ui/components/StackPanel.h>

namespace game {
class BaseMenuState : public engine::State {
private:
    common::Vector2D<int> m_screenSize{};

protected:
    std::unique_ptr<engine::ui::UISystem> m_uiSystem;
    virtual void prependButtons(engine::ui::StackPanel& panel) = 0;
    virtual void appendButtons(engine::ui::StackPanel& panel) = 0;

public:
    explicit BaseMenuState(engine::IGame& context);

    void init() override;
    void resume() override;
    void pause() override;
    void update(std::chrono::nanoseconds timeStep) override;
    void render(engine::IRenderer& renderer) override;

    void close() override;
};
}