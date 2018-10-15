#pragma once

#include <chrono>
#include <engine/ui/UISystem.h>
#include <game/State.h>
#include <input/IObserver.h>

namespace game {
class MainMenuState : public engine::State, engine::input::IObserver {
private:
    std::unique_ptr<engine::ui::UISystem> m_system;

public:
    explicit MainMenuState(engine::IGame& game);

    void init() override;
    void update(std::chrono::nanoseconds timeStep) override;
    void render(engine::IRenderer& renderer) override;

private:
    void onInputUpdate(std::map<engine::input::Keys, std::shared_ptr<engine::events::IControlEvent>> &keymap) override;
};
}
