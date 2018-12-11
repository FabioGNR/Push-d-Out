#include "ConfigurationRepository.h"
#include <fstream>
#include <game/exceptions/CanNotSaveConfigException.h>

namespace game::config {
Configuration ConfigurationRepository::get()
{
    Configuration config{};
    std::ifstream file(CONFIG_PATH);
    if (!file.good()) {
        return config; // return a default config if no file was found
    }
    json j;
    file >> j;
    config = j; // this calls the from_json method defined below
    return config;
}

void ConfigurationRepository::save(const Configuration& config)
{
    json j = config; // this calls the to_json method defined below
    std::ofstream file(CONFIG_PATH); // default file mode opens for overwrite
    if (file.is_open()) {
        file << j;
    } else {
        throw exceptions::CanNotSaveConfigException();
    }
}

void to_json(json& j, const Configuration& c)
{
    j = json{
        { "sound", c.sound },
        { "assets", c.assets }
    };
}

void from_json(const json& j, Configuration& c)
{
    c.sound = j.at("sound").get<Sound>();
    c.assets = j.at("assets").get<std::string>();
}

void to_json(json& j, const Sound& s)
{
    j = json{
        { "sfxVolume", s.sfxVolume },
        { "musicVolume", s.musicVolume },
        { "masterVolume", s.masterVolume }
    };
}

void from_json(const json& j, Sound& s)
{
    s.sfxVolume = j.at("sfxVolume").get<int>();
    s.musicVolume = j.at("musicVolume").get<int>();
    s.masterVolume = j.at("masterVolume").get<int>();
}
}
