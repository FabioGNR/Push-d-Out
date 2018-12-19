#pragma once

#include "BaseMenuState.h"

namespace game {
class PauseMenuState : public BaseMenuState {
    engine::Sprite m_backgroundOverlay;

public:
    explicit PauseMenuState(engine::IGame& context);
    void render(engine::IRenderer& renderer) override;

protected:
    void prependButtons(engine::ui::StackPanel& panel) override;
    void appendButtons(engine::ui::StackPanel& panel) override;
};
}
