#pragma once

#include <engine/events/models/Subscription.h>
#include <engine/game/State.h>
#include <engine/input/InputManager.h>

#include "game/level/editor/Editor.h"

namespace game {
class LevelEditorState : public engine::State {
    level::Editor m_editor;

    engine::input::InputManager& m_inputManager;
    std::shared_ptr<engine::events::Subscription<engine::input::maps::InputMap>> m_inputSubscription;

public:
    explicit LevelEditorState(engine::IGame& context);

    void init() override;
    void update(std::chrono::nanoseconds timeStep) override;
    void render(engine::IRenderer& renderer) override;
};
}
