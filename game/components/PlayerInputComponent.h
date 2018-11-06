#pragma once

#include "game/definitions/Action.h"
#include <engine/ecs/Component.h>
#include <engine/input/Keys.h>
#include <iostream>
#include <map>

namespace game {
namespace components {
    struct PlayerInputComponent : public engine::ecs::BaseComponent<PlayerInputComponent> {
        int controllerId;
        std::map<definitions::Action, engine::input::Keys> controls;

        PlayerInputComponent(int controllerId, std::map<definitions::Action, engine::input::Keys> controls)
            : controllerId(controllerId)
            , controls(std::move(controls)){};
    };
}
}
