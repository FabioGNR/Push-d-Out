#include "LevelEditorState.h"

namespace game {

void LevelEditorState::close() {
    State::close();
}
void LevelEditorState::update(std::chrono::nanoseconds timeStep) {

}
void LevelEditorState::render(engine::IRenderer &renderer) {

}
void LevelEditorState::init() {
    State::init();
}
void LevelEditorState::resume() {
    State::resume();
}
void LevelEditorState::pause() {
    State::pause();
}
}
