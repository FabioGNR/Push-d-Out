#pragma once

#include "BaseMenuState.h"
#include <engine/ui/components/Button.h>

namespace game {
class PauseMenuState : public BaseMenuState {
    std::shared_ptr<engine::ui::Button> m_resumeButton;

public:
    explicit PauseMenuState(engine::input::InputManager& inputManager);

    void onResumeClick(std::function<void()> action);
};
}
