#pragma once

#include <engine/game/State.h>
#include <engine/ui/UISystem.h>

#include <chrono>

namespace engine {
namespace ui {
    class StackPanel;
    class Component;
}
namespace input {
    class InputManager;
}
}

namespace game {
class BaseMenuState : public engine::State {
    std::shared_ptr<engine::ui::StackPanel> m_buttonStack;
    std::unique_ptr<engine::ui::UISystem> m_uiSystem;

public:
    explicit BaseMenuState(engine::input::InputManager& inputManager);

    void init() override;
    void resume() override;
    void pause() override;
    void update(std::chrono::nanoseconds timeStep) override;
    void render(engine::IRenderer& renderer) override;

    void close() override;

    void appendComponent(std::shared_ptr<engine::ui::Component> component);
    void prependComponent(std::shared_ptr<engine::ui::Component> component);
};
}