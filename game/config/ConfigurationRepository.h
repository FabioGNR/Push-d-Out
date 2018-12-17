#pragma once
#include "Configuration.h"
#include "external/JSON/json.hpp"

using json = nlohmann::json;

namespace game::config {
class ConfigurationRepository {
    constexpr static const char* CONFIG_PATH = "config.json";

public:
    static Configuration get();
    void save(const Configuration& config);
};

void to_json(json&, const Sound&);
void from_json(const json&, Sound&);
void to_json(json& j, const Configuration& c);
void from_json(const json& j, Configuration& c);
}