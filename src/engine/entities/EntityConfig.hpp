#ifndef ENTITYCONFIG_HPP
    #define ENTITYCONFIG_HPP

#include <string>
#include <vector>
#include <optional>
#include <nlohmann/json.hpp>
#include <fstream>

#include "src/components/vision.hpp"
#include "src/components/hitbox.hpp"

namespace Engine {
namespace Entities {
    // Structure to hold the parsed data
    struct Config {
        std::string name;
        bool playable = false;
        std::string sprite;
        std::optional<std::string> script_file;
        std::optional<std::string> default_behavior_fun;
        int steps_sound_strength = 10;
        std::vector<std::string> components;
        std::vector<double> world_position;
        std::optional<Components::HitboxData> hitbox_specs;

        Components::VisionConfig vision_config;
    };

// Function to parse JSON into VisionConfig struct
Config getEntityConfigFromJson(const std::string& jsonPath) {
    std::ifstream f(jsonPath);
    nlohmann::json j = nlohmann::json::parse(f);
    Config config;

    if (j.contains("script_file") == true && j.contains("default_behavior_fun")) {
        config.script_file = j["script_file"];
        config.default_behavior_fun = j["default_behavior_fun"];
    }
    config.name = j["name"];
    config.sprite = j["sprite"];
    config.steps_sound_strength = j["steps_sound_strength"];
    config.vision_config.vision_strength_meter = j["vision_strength_meter"];
    config.components = j["components"].get<std::vector<std::string>>();
    config.world_position = j["world_position"].get<std::vector<double>>();
    for (const auto& script : j["vision_scripts"]) {
        Components::VisionConfig::VisionScript vs;

        if (script.contains("target_id") == true) {
            vs.target_id = script["target_id"];
        } else {
            vs.target_id = 0;
        }
        vs.fun = script["fun"];
        vs.priority = script["priority"];
        config.vision_config.vision_scripts.push_back(vs);
    }
    config.default_behavior_fun = j["default_behavior_fun"];

    if (j.contains("hitbox") && j["hitbox"].contains("size") &&
        j["hitbox"].contains("layer") && j["hitbox"].contains("collideWith")) {
            config.hitbox_specs = Components::HitboxData{
                {j["hitbox"]["size"]["x"].get<unsigned int>(), j["hitbox"]["size"]["y"].get<unsigned int>()},
                j["hitbox"]["layer"].get<std::string>(),
                j["hitbox"]["collideWith"].get<std::vector<std::string>>()
            };
        std::cout << "Hitbox size: " << config.hitbox_specs->hitboxSize.x << " : " << config.hitbox_specs->hitboxSize.y
        << "\nLayer : " << config.hitbox_specs->layer << " colliding with layers : ";
        for (const auto& layer : config.hitbox_specs->collidingLayers) {
            std::cout << layer << " ";
        }
        std::cout << std::endl;
    }

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
