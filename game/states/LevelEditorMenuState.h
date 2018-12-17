#pragma once

#include "BaseMenuState.h"
#include "game/level/editor/Editor.h"

namespace game {
class LevelEditorMenuState : public BaseMenuState {
    level::Editor* m_editor;

public:
    explicit LevelEditorMenuState(level::Editor* editor, engine::IGame& context);

protected:
    void prependButtons(engine::ui::StackPanel& panel) override;
    void appendButtons(engine::ui::StackPanel& panel) override;
};
}
