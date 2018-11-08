#pragma once

#include "BaseMenuState.h"
#include <chrono>

namespace game {
class MainMenuState : public BaseMenuState {

public:
    explicit MainMenuState(engine::IGame& context);

protected:
    void prependButtons(engine::ui::StackPanel& panel) override;

    void appendButtons(engine::ui::StackPanel& panel) override;
};
}
