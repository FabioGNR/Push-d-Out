#pragma once

#include "BaseMenuState.h"
#include "game/level/editor/Editor.h"

namespace game {
class LevelEditorMenuState : public BaseMenuState {
    level::Editor* m_editor;
    engine::Sprite m_backgroundOverlay;

public:
    explicit LevelEditorMenuState(level::Editor* editor, engine::IGame& context);
    void render(engine::IRenderer& renderer) override;

protected:
    void prependButtons(engine::ui::StackPanel& panel) override;
    void appendButtons(engine::ui::StackPanel& panel) override;
};
}
