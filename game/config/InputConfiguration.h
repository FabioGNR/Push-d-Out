#pragma once
#include <engine/input/AnalogKeys.h>
#include <engine/input/Keys.h>
#include <game/definitions/Action.h>
#include <map>

namespace game::config {
class InputConfiguration {
public:
    std::map<game::definitions::Action, engine::input::Keys> getKeyboardControls() const;
    std::map<game::definitions::Action, engine::input::Keys> getControllerControls() const;
    std::map<game::definitions::Action, engine::input::AnalogKeys> getAnalogControls() const;
};
}