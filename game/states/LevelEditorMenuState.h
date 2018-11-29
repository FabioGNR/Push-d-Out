#pragma once

#include "BaseMenuState.h"

namespace game {
class LevelEditorMenuState : public BaseMenuState {
public:
    LevelEditorMenuState(engine::IGame& context);

protected:
    void prependButtons(engine::ui::StackPanel& panel) override;
    void appendButtons(engine::ui::StackPanel& panel) override;
};
}
