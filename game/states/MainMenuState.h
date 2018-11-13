#pragma once

#include <engine/events/models/Subscription.h>
#include <engine/game/State.h>
#include <engine/ui/UISystem.h>
#include <engine/input/maps/KeyMap.h>
#include "BaseMenuState.h"
#include <chrono>
#include <engine/sound/ISoundManager.h>

namespace game {
class MainMenuState : public BaseMenuState {
private:
    std::unique_ptr<engine::sound::ISoundManager> m_soundManager;

public:
    explicit MainMenuState(engine::IGame& context);

protected:
    void prependButtons(engine::ui::StackPanel& panel) override;
    void appendButtons(engine::ui::StackPanel& panel) override;

public:
    void resume() override;
    void pause() override;
    void close() override;
    void init() override;
};
}
