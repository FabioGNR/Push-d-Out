#pragma once

#include <engine/game/State.h>

namespace game {
class LevelEditorState : public engine::State {
 public:

  ~LevelEditorState() override = default;
  void update(std::chrono::nanoseconds timeStep) override;
  void render(engine::IRenderer &renderer) override;
  void init() override;
  void resume() override;
  void pause() override;
  void close() override;
};
}
