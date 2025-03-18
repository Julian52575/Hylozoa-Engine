#ifndef ENTITY_HPP
    #define ENTITY_HPP

#include <exception>
#include <memory>
#include <optional>
#include <rengine/Rengine.hpp>
#include <nlohmann/json.hpp>
#include <rengine/src/Entity.hpp>
#include <stdexcept>
#include <string>

#include "EntityConfig.hpp"
#include "Script.hpp"
#include "src/components/configuration.hpp"
#include "src/components/position.hpp"
#include "src/components/sprite.hpp"
#include "src/components/vision.hpp"
#include "src/components/hitbox.hpp"
#include "src/lib/Singleton.hpp"
#include "src/engine/LoggingManager.hpp"

namespace Engine {
namespace Entities {

    class Entity {
        public:
            using size_type = typename Rengine::Entity::size_type;
            Entity(const std::string& configPath)
            {
                try {
                    Config con = getEntityConfigFromJson(configPath);

                    if (isConfigValid(con) == false) {
                        throw std::runtime_error("Not valid.");
                    }
                    if (con.script_file.has_value()) {
                        this->_script = Script(con.script_file.value(), con.default_behavior_fun.value());
                    }
                    this->addComponents(configPath, con);
                } catch (std::exception &e) {
                    throw std::runtime_error(std::string("Error on entity constructor from config file '")
                        + configPath
                        + std::string("':\n")
                        + e.what()
                    );
                }
            }
            ~Entity() = default;
            operator int(void) const
            {
                if (this->_id.has_value() == false) {
                    throw std::runtime_error("Bad int() on non-set entity id");
                }
                return this->_id.value();
            }

        protected:
            void addComponents(const std::string& configPath, const Config& con)
            {
                Rengine::Entity en = Lib::Singleton<Rengine::ECS>::getInstance().addEntity();

                this->_id = en;
                en.addComponent<Components::Position>(con.world_position[0], con.world_position[1]);
                if (con.components.size() == 0) {
                    return;
                }
                for (auto currentName : con.components) {
                    if (currentName == "vision") {
                        en.addComponent<Components::Vision>(con.vision_config);
                    } else if (currentName == "sprite") {
                        if (con.sprite.find("/") == true) {
                            en.addComponent<Components::Sprite>(con.sprite);
                        } else {
                            auto configDirIdx = configPath.find_last_of('/');

                            if (configDirIdx == std::string::npos) {
                                en.addComponent<Components::Sprite>(con.sprite);
                            } else {
                                en.addComponent<Components::Sprite>(configPath.substr(0, configDirIdx + 1) + con.sprite);
                            }
                        }
                    } else if (currentName == "hearing") {
                        Lib::Singleton<LoggingManager>::getInstance() << "Warning: hearing module not implemented.\n";
                    }
                    if (currentName == "hitbox") {
                        if (con.hitbox_specs.has_value()) {
                            en.addComponent<Components::Hitbox>(con.hitbox_specs.value());
                            std::cout << "hitbox added successfully" << std::endl;
                        } else {
                            std::cerr << "Specs error" << std::endl;
                            throw std::runtime_error("No hitbox specs provided.");
                        }
                    }
                }
                en.addComponent<Components::Position>(con.world_position[0], con.world_position[1]);
                en.addComponent<Components::Configuration>(con);
            }

        protected:
            // lua script
            // std::optional< script> _script;
            std::string _name;
            std::optional<Config> _config;
            std::optional<size_type> _id;
            std::optional<Script> _script;

    };
}  // namespace Entities
}  // namespace Engine

#endif  // ENTITY_HPP
