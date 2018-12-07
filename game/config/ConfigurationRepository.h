#pragma once
#include "UserConfig.h"
#include "external/JSON/json.hpp"

using json = nlohmann::json;

namespace game::config {
class ConfigurationRepository {
    constexpr static const char* CONFIG_PATH = "user-config.json";

public:
    void saveConfig(const UserConfig& config);
    UserConfig readConfig() const;
};

void to_json(json& j, const UserConfig& c);
void from_json(const json& j, UserConfig& c);
}