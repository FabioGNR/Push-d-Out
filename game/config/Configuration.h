#pragma once

#include <string>

namespace game::config {
struct Sound {
    int masterVolume{ 100 };
    int sfxVolume{ 100 };
    int musicVolume{ 100 };
};

struct Configuration {
    Sound sound;
    std::string assets = "assets/";
};
}
