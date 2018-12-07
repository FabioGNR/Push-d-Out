#pragma once

#include "BaseMenuState.h"
#include <chrono>
#include <engine/events/models/Subscription.h>
#include <engine/game/State.h>
#include <engine/sound/ISoundManager.h>
#include <engine/ui/UISystem.h>

namespace game {
class MainMenuState : public BaseMenuState {
private:
    engine::sound::ISoundManager* m_soundManager{};

protected:
    void prependButtons(engine::ui::StackPanel& panel) override;
    void appendButtons(engine::ui::StackPanel& panel) override;

    void openCreditsFrame();

public:
    explicit MainMenuState(engine::IGame& context);

    void resume() override;
    void pause() override;
    void close() override;
    void init() override;
};
}
