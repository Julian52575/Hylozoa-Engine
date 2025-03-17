// julian.bottiglione@epitech.eu

#ifndef ENGINE_WORLD_WORLD_HPP
    #define ENGINE_WORLD_WORLD_HPP

#include <exception>
#include <memory>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <rengine/src/ECS.hpp>
#include <rengine/src/Graphics/ASprite.hpp>
#include <rengine/src/Graphics/GraphicManager.hpp>
#include <rengine/src/Graphics/SpriteSpecs.hpp>
#include <rengine/src/SparseArray.hpp>
#include <stdexcept>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <rengine/RengineGraphics.hpp>

#include "src/components/position.hpp"
#include "src/components/sprite.hpp"
#include "src/engine/LoggingManager.hpp"
#include "src/engine/entities/Entity.hpp"
#include "src/lib/Singleton.hpp"

namespace Engine {

    class World {
        public:
            World(const std::string& configPath)
            {
                Lib::Singleton<Engine::LoggingManager>::getInstance() << "World constructor with '";
                Lib::Singleton<Engine::LoggingManager>::getInstance() << configPath << "'\n"; ////////////

                try {
                    std::ifstream f(configPath);
                    nlohmann::json j = nlohmann::json::parse(f);
                    std::string config_dir = "";

                    if (j.contains("entities") == false) {
                        throw std::runtime_error("No entities field.");
                    }
                    if (j["entities"].is_array() == false
                    || j["entities"].size() == 0) {
                        throw std::runtime_error("entities field is either not an array or is empty");
                    }
                    if (j.contains("config_dir") == true) {
                        config_dir = j["config_dir"];
                        if (config_dir[config_dir.length()] != '/') {
                            config_dir += '/';
                        }
                    }
                    for (const auto& currentConfig : j["entities"]) {
                        if (currentConfig.is_string() == false) {
                            throw std::runtime_error("Invalid element in entities array");
                        }
                        Engine::Entities::Entity en = Engine::Entities::Entity(config_dir + std::string(currentConfig));

                        this->_entityList.push_back(Engine::Entities::Entity::size_type(en));
                        std::cout << "Added " << en << " to world" << std::endl;  ////////
                    }
                } catch (std::exception &e) {
                    throw std::runtime_error(
                        std::string("Got exception on world constructor with config file '")
                        + configPath
                        + std::string(":\n")
                        + e.what()
                    );
                }
                this->initGround();
            }
            ~World() = default;
            void render()
            {
                this->renderGround();
                Rengine::SparseArray<Components::Sprite>& sp = Lib::Singleton<Rengine::ECS>::getInstance().getComponents<Components::Sprite>();
                Rengine::SparseArray<Components::Position>& pos = Lib::Singleton<Rengine::ECS>::getInstance().getComponents<Components::Position>();

                for (auto &eId : this->_entityList) {
                    if (sp[eId].has_value() == false) {
                        continue;
                    }
                    if (pos[eId].has_value() == false) {
                        continue;
                    }
                    sp[eId]->render(pos[eId].value());
                }
            }

        private:
            inline void initGround()
            {
                Rengine::Graphics::SpriteSpecs specs;

                specs.texturePath = "assets/ground.jpg";
                specs.textureScale.x = 3;
                this->_groundSprite = Rengine::Graphics::GraphicManagerSingletone::get().createSprite(specs);
            }
            inline void renderGround()
            {
                Rengine::Graphics::GraphicManagerSingletone::get().addToRender(this->_groundSprite, {0, 800});
            }

        private:
            std::vector<Engine::Entities::Entity::size_type> _entityList;
            std::shared_ptr<Rengine::Graphics::ASprite> _groundSprite;
    };  // World
}  // Engine

#endif  // ENGINE_WORLD_WORLD_HPP
