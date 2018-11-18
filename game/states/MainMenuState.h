#pragma once

#include "BaseMenuState.h"
#include <chrono>
#include <engine/events/models/Subscription.h>
#include <engine/game/State.h>
#include <engine/input/maps/KeyMap.h>
#include <engine/sound/ISoundManager.h>
#include <engine/ui/UISystem.h>

namespace game {
class MainMenuState : public BaseMenuState {
private:
    std::unique_ptr<engine::sound::ISoundManager> m_soundManager;

public:
    explicit MainMenuState(engine::IGame& context);

protected:
    void prependButtons(engine::ui::StackPanel& panel) override;
    void appendButtons(engine::ui::StackPanel& panel) override;

    void openCreditsFrame();

public:
    void resume() override;
    void pause() override;
    void close() override;
    void init() override;
};
}
