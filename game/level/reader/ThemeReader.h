#pragma once

#include "Reader.h"
#include <game/level/Theme.h>

namespace game {
namespace level {
    class ThemeReader : public Reader<Theme> {
    public:
        ~ThemeReader() override = default;
        Theme build(const json& j) override;
    };
}
}
