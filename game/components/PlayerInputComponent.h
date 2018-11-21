#pragma once

#include "engine/input/AnalogKeys.h"
#include "game/definitions/Action.h"
#include <engine/ecs/Component.h>
#include <engine/input/Keys.h>
#include <iostream>
#include <map>

namespace game {
namespace components {
    struct PlayerInputComponent : public engine::ecs::BaseComponent<PlayerInputComponent> {
    private:
        std::map<definitions::Action, engine::input::Keys> controls;
        std::map<definitions::Action, engine::input::AnalogKeys> analogControls;

    public:
        const int controllerId;

        PlayerInputComponent(int controllerId, std::map<definitions::Action, engine::input::Keys> controls, std::map<definitions::Action, engine::input::AnalogKeys> analogControls)
            : controls(std::move(controls))
            , analogControls(std::move(analogControls))
            , controllerId(controllerId){};

        engine::input::AnalogKeys getAnalog(definitions::Action action)
        {
            if (analogControls.find(action) == analogControls.end()) {
                return engine::input::AnalogKeys::CON_UNKNOWN;
            }
            return analogControls.at(action);
        }

        engine::input::Keys getKey(definitions::Action action)
        {
            if (controls.find(action) == controls.end()) {
                return engine::input::UNKNOWN;
            }
            return controls.at(action);
        }
    };
}
}
