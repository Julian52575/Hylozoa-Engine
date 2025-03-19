// julian.bottiglione@epitech.eu

#ifndef ENGINE_WORLD_WORLD_HPP
    #define ENGINE_WORLD_WORLD_HPP

#include <cstddef>
#include <exception>
#include <functional>
#include <memory>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <optional>
#include <rengine/src/ECS.hpp>
#include <rengine/src/Entity.hpp>
#include <rengine/src/Graphics/ASprite.hpp>
#include <rengine/src/Graphics/GraphicManager.hpp>
#include <rengine/src/Graphics/SpriteSpecs.hpp>
#include <rengine/src/Graphics/Vector.hpp>
#include <rengine/src/SparseArray.hpp>
#include <stdexcept>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <rengine/RengineGraphics.hpp>

#include "src/components/hitbox.hpp"
#include "src/components/playable.hpp"
#include "src/components/position.hpp"
#include "src/components/sprite.hpp"
#include "src/components/velocity.hpp"
#include "src/components/vision.hpp"
#include "src/engine/LoggingManager.hpp"
#include "src/engine/entities/Entity.hpp"
#include "src/engine/options/options.hpp"
#include "src/lib/Singleton.hpp"

namespace Engine {

    class World {
        public:
            World(const std::string& configPath)
            {
                // Parse World config
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
                        if (currentConfig.contains("config") == false) {
                            throw std::runtime_error("No 'config' field in 'entities' array");
                        }
                        std::string configPath = std::string(currentConfig["config"]);
                        Engine::Entities::Entity en = Engine::Entities::Entity(config_dir + configPath);

                        this->_entityList.push_back(Engine::Entities::Entity::size_type(en));
                        if (currentConfig.contains("playable") == true
                        && currentConfig["playable"].is_boolean() == true) {
                            Rengine::Entity& rengineEntity = Lib::Singleton<Rengine::ECS>::getInstance().getEntity(int(en));

                            rengineEntity.addComponent<Components::Playable>();
                            Lib::Singleton<Engine::LoggingManager>::getInstance() << "Applied playable to entity #" << Rengine::Entity::size_type(en) << "\n";
                        }
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
                Rengine::SparseArray<Components::Sprite>& sprites
                    = Lib::Singleton<Rengine::ECS>::getInstance().getComponents<Components::Sprite>();
                Rengine::SparseArray<Components::Position>& positions
                    = Lib::Singleton<Rengine::ECS>::getInstance().getComponents<Components::Position>();
                std::optional<std::reference_wrapper<Rengine::SparseArray<Components::Vision>>> maybeVisions = std::nullopt;
                std::optional<std::reference_wrapper<Rengine::SparseArray<Components::Hitbox>>> maybeHitboxs = std::nullopt;

                // Set vision sparse array if Vision Circle debug is set
                if (Lib::Singleton<Options::Debug>::getInstance().showVision == true) {
                    maybeVisions = Lib::Singleton<Rengine::ECS>::getInstance().getComponents<Components::Vision>();
                    maybeHitboxs = Lib::Singleton<Rengine::ECS>::getInstance().getComponents<Components::Hitbox>();
                }
                // Parse all entities up the highest id
                for (Rengine::ECS::size_type eId = 0; eId <= Lib::Singleton<Rengine::ECS>::getInstance().getHighestEntityId(); eId++) {
                    // Ensure entity id is active
                    if (Lib::Singleton<Rengine::ECS>::getInstance().isEntityActive(eId) == false) {
                        continue;
                    }
                    // Ensure entity has both a sprite and a position
                    if (sprites[eId].has_value() == false
                    || positions[eId].has_value() == false) {
                        continue;
                    }
                    sprites[eId]->render(positions[eId].value());
                    // Render Vision Circle if the Vision Sparse Array was set previously
                    if (maybeVisions != std::nullopt
                    && maybeVisions->get()[eId].has_value() == true
                    && maybeHitboxs != std::nullopt
                    && maybeHitboxs->get()[eId].has_value() == true) {
                        this->renderVisionCircle(maybeVisions->get()[eId].value(),
                            positions[eId].value(), maybeHitboxs->get()[eId].value());
                    }
                }
            }
            void applyGravityToEntities()
            {
                Rengine::SparseArray<Components::Hitbox>& hitboxs
                    = Lib::Singleton<Rengine::ECS>::getInstance().getComponents<Components::Hitbox>();
                Rengine::SparseArray<Components::Velocity>& velocities
                    = Lib::Singleton<Rengine::ECS>::getInstance().getComponents<Components::Velocity>();
                Rengine::SparseArray<Components::Position>& positions
                    = Lib::Singleton<Rengine::ECS>::getInstance().getComponents<Components::Position>();
                double x = 0.0;
                double y = 0.0;
                Components::HitboxData hitboxData;

                for (Rengine::ECS::size_type eId = 0; eId <= Lib::Singleton<Rengine::ECS>::getInstance().getHighestEntityId(); eId++) {
                    // Ignore entities that miss the components
                    if (hitboxs[eId].has_value() == false
                    || velocities[eId].has_value() == false
                    || positions[eId].has_value() == false) {
                        continue;
                    }
                    positions[eId]->get(x, y);
                    hitboxs[eId]->get(hitboxData);
                    // Do nothing on grounded entity
                    if (y - (hitboxData.hitboxSize.y / 2) >= this->_groundY) {
                        continue;
                    }
                    velocities[eId]->getY() += this->_fallingSpeed;
                }
            }
            void applyVelocityToEntities()
            {
                Rengine::SparseArray<Components::Hitbox>& hitboxs
                    = Lib::Singleton<Rengine::ECS>::getInstance().getComponents<Components::Hitbox>();
                Rengine::SparseArray<Components::Velocity>& velocities
                    = Lib::Singleton<Rengine::ECS>::getInstance().getComponents<Components::Velocity>();
                Rengine::SparseArray<Components::Position>& positions
                    = Lib::Singleton<Rengine::ECS>::getInstance().getComponents<Components::Position>();
                Components::HitboxData hitboxData;

                for (Rengine::ECS::size_type eId = 0; eId <= Lib::Singleton<Rengine::ECS>::getInstance().getHighestEntityId(); eId++) {
                     // Ignore entities that miss the components
                    if (hitboxs[eId].has_value() == false
                    || velocities[eId].has_value() == false
                    || positions[eId].has_value() == false) {
                        continue;
                    }
                    // Update positions
                    positions[eId]->getX() += (velocities[eId]->getX() * 8.4);
                    positions[eId]->getY() += (velocities[eId]->getY() * 7.8);
                    // Reset velocity
                    velocities[eId]->getX() = 0;
                    velocities[eId]->getY() = 0;
                    // Ground correction
                    hitboxs[eId]->get(hitboxData);
                    if (positions[eId]->getY() + (hitboxData.hitboxSize.y / 2) >= this->_groundY) {
                        positions[eId]->getY() = this->_groundY - (hitboxData.hitboxSize.y / 2);
                    }
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
                Rengine::Graphics::GraphicManagerSingletone::get().addToRender(this->_groundSprite, {0, (float) this->_groundY});
            }

        private:
            inline void initVisionCircle()
            {
                this->_visionCircleSpecs.type = Rengine::Graphics::SpriteTypeCircle;
                this->_visionCircleSpecs.opacity = 0.0;
                this->_visionCircleSpecs.shapeData.outlineColor = {255, 0, 0};
                this->_visionCircleSpecs.shapeData.outlineThickness = 2.0;
                this->_visionCircle = Rengine::Graphics::GraphicManagerSingletone::get().createSprite(
                    this->_visionCircleSpecs
                );
            }
            inline void renderVisionCircle(const Components::Vision& vis, const Components::Position& pos, const Components::Hitbox& hit)
            {
                if (this->_visionCircle == nullptr) {
                    this->initVisionCircle();
                }
                Rengine::Graphics::vector2D<double> posVector;
                Components::HitboxData hitboxData;

                // Update circle radius to match vision strength
                this->_visionCircleSpecs.shapeData.specifics.circleRadius = (float) vis.getVisionStrength();
                this->_visionCircleSpecs.originOffset.x = (float) vis.getVisionStrength();
                this->_visionCircleSpecs.originOffset.y = (float) vis.getVisionStrength();
                this->_visionCircle->updateSpriteSpecs(this->_visionCircleSpecs);
                // a
                pos.get(posVector.x, posVector.y);
                hit.get(hitboxData);
                Rengine::Graphics::GraphicManagerSingletone::get().addToRender(this->_visionCircle,
                {
                    (float) posVector.x ,//- hitboxData.hitboxSize.x,
                    (float) posVector.y //- hitboxData.hitboxSize.y
                    }
                );
            }

        private:
            Rengine::Graphics::SpriteSpecs _visionCircleSpecs;
            std::shared_ptr<Rengine::Graphics::ASprite> _visionCircle = nullptr;

        private:
            double _groundY = 900;
            double _fallingSpeed = 0.8;
            std::shared_ptr<Rengine::Graphics::ASprite> _groundSprite = nullptr;
            std::vector<Engine::Entities::Entity::size_type> _entityList;
    };  // World
}  // Engine

#endif  // ENGINE_WORLD_WORLD_HPP
