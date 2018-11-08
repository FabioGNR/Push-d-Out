#pragma once

#include "BaseMenuState.h"

namespace game {
class PauseMenuState : public BaseMenuState {

public:
    explicit PauseMenuState(engine::IGame& context);

protected:
    void prependButtons(engine::ui::StackPanel& panel) override;

    void appendButtons(engine::ui::StackPanel& panel) override;
};
}
