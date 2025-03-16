#ifndef ENTITYCONFIG_HPP
    #define ENTITYCONFIG_HPP

#include <string>
#include <vector>
#include <optional>
#include <nlohmann/json.hpp>

#include "src/components/vision.hpp"

namespace Engine {
namespace Entities {
    // Structure to hold the parsed data
    struct Config {
        std::optional<std::string> script_file;
        std::optional<std::string> default_behavior_fun;
        int steps_sound_strength = 10;
        std::vector<std::string> components;
        std::vector<int> world_position;

        Components::VisionConfig vision_config;
    };

// Function to parse JSON into VisionConfig struct
Config getConfigFromJson(const std::string& jsonString) {
    nlohmann::json j = nlohmann::json::parse(jsonString);
    Config config;

    if (j.contains("script_file") == true && j.contains("default_behavior_fun")) {
        config.script_file = j["script_file"];
        config.default_behavior_fun = j["default_behavior_fun"];
    }
    config.steps_sound_strength = j["steps_sound_strength"];
    config.vision_config.vision_strength_meter = j["vision_strength_meter"];
    config.components = j["components"].get<std::vector<std::string>>();
    config.world_position = j["world_position"].get<std::vector<int>>();

    for (const auto& script : j["vision_scripts"]) {
        Components::VisionConfig::VisionScript vs;

        vs.id = script["id"];
        vs.fun = script["fun"];
        vs.priority = script["priority"];
        config.vision_config.vision_scripts.push_back(vs);
    }
    config.default_behavior_fun = j["default_behavior_fun"];
    return config;
}

bool isConfigValid(const Config& config)
{
    if (config.world_position.size() < 2) {
        return false;
    }
    return true;
}

}  // namespace Entities
}  // namespace Engine

#endif  // ENTITYCONFIG_HPP
