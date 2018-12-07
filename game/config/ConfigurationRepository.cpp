#include "ConfigurationRepository.h"
#include <fstream>
#include <game/exceptions/CanNotSaveConfigException.h>

namespace game::config {
UserConfig ConfigurationRepository::readConfig() const
{

    UserConfig config{};
    std::ifstream file(CONFIG_PATH);
    if (!file.good()) {
        return config; // return a default config if no file was found
    }
    json j;
    file >> j;
    config = j; // this calls the from_json method defined below
    return config;
}

void ConfigurationRepository::saveConfig(const UserConfig& config)
{
    json j = config; // this calls the to_json method defined below
    std::ofstream file(CONFIG_PATH); // default file mode opens for overwrite
    if (file.is_open()) {
        file << j;
    } else {
        throw exceptions::CanNotSaveConfigException();
    }
}

void to_json(json& j, const UserConfig& c)
{
    j = json{
        { "sfxVolume", c.sfxVolume },
        { "musicVolume", c.musicVolume },
        { "masterVolume", c.masterVolume }
    };
}

void from_json(const json& j, UserConfig& c)
{
    c.sfxVolume = j.at("sfxVolume").get<int>();
    c.musicVolume = j.at("musicVolume").get<int>();
    c.masterVolume = j.at("masterVolume").get<int>();
}
}
