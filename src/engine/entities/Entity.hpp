#ifndef ENTITY_HPP
    #define ENTITY_HPP

#include <exception>
#include <optional>
#include <rengine/Rengine.hpp>
#include <nlohmann/json.hpp>
#include <rengine/src/Entity.hpp>
#include <stdexcept>
#include <string>

#include "EntityConfig.hpp"
#include "Script.hpp"
#include "src/lib/Singleton.hpp"
#include "src/engine/LoggingManager.hpp"

namespace Engine {
namespace Entities {
    class Entity {
        public:
            Entity(Rengine::ECS& ecs, const std::string& config)
                : _ecs(ecs)
            {
                try {
                    Config con = getConfigFromJson(config);

                    if (isConfigValid(con) == false) {
                        throw std::runtime_error("Not valid.");
                    }
                    if (con.script_file.has_value()) {
                        this->_script = Script(con.script_file.value(), con.default_behavior_fun.value());
                    }
                    Rengine::Entity& entity = this->_ecs.addEntity();

                    if (con.components.size() == 0) {
                        goto skipComponents;
                    }
                    this->_id = entity;
                    for (std::size_t i = 0; i < con.components.size(); i++) {
                        this->addComponent(con, i, entity);
                    }
skipComponents:     ;
                    Lib::Singleton<Engine::LoggingManager>::getInstance() << "Created entity ";
                    Lib::Singleton<Engine::LoggingManager>::getInstance() << std::to_string(entity);
                    Lib::Singleton<Engine::LoggingManager>::getInstance().endl();
                } catch (std::exception &e) {
                    std::cerr << "Error on entity constructor: " << e.what() << std::endl;
                }
            }
            ~Entity() = default;

        protected:
            void addComponent(const Config& con, const std::size_t  componentIdx)
            {
                if (con.components.size() <= componentIdx) {
                    throw std::runtime_error("Bad index");
                }
                if (this->_id.has_value() == false) {
                    throw std::runtime_error("No entity id.");
                }
                return this->addComponent(con, componentIdx, this->_ecs.getEntity(this->_id.value()));
            }
            void addComponent(const Config& con, const std::size_t componentId, Rengine::Entity& ownEntity)
            {
                const std::string& name = con.components[componentId];

                if (name == "vision") {

                } else if (name == "hearing") {

                }
            }

        protected:
            Rengine::ECS& _ecs;
            // lua script
            // std::optional< script> _script;
            std::string _name;
            std::optional<Config> _config;
            std::optional<Rengine::Entity::size_type> _id;
            std::optional<Script> _script;
    };
}  // namespace Entities
}  // namespace Engine

#endif  // ENTITY_HPP
