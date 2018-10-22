#pragma once

#include "game/definitions/Action.h"
#include <engine/ecs/Component.h>
#include <iostream>
#include <map>
#include <engine/input/Keys.h>

namespace game {
namespace components {
    struct PlayerInputComponent : public engine::ecs::BaseComponent<PlayerInputComponent> {
        int controllerId;
        std::map<definitions::Action, engine::input::Keys> controls;

        PlayerInputComponent(int controllerId, std::map<definitions::Action, engine::input::Keys> controls)
            : controllerId(controllerId)
            , controls(controls) {};
    };
}
}
