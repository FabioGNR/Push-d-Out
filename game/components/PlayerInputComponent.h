#pragma once

#include "game/definitions/Action.h"
#include <engine/ecs/Component.h>
#include <iostream>
#include <map>

namespace game {
namespace components {
    struct PlayerInputComponent : public engine::BaseComponent<PlayerInputComponent> {
        int controllerId;
        // TODO: Replace char with the key scheme made by Richard
        std::map<definitions::Action, char> controls;

        PlayerInputComponent(int controllerId, std::map<definitions::Action, char> controls)
            : controllerId(controllerId)
            , controls(controls) {};
    };
}
}
