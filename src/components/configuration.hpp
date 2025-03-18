//

#ifndef COMPONENTS_CONFIGURATIONS_HPP
    #define COMPONENTS_CONFIGURATIONS_HPP

#include "src/engine/entities/EntityConfig.hpp"
namespace Components {

    class Configuration {
        public:
            Configuration() = default;
            Configuration(const Engine::Entities::Config& config)
                : _config(config) {}
            ~Configuration() = default;
            const Engine::Entities::Config& getConfig() const noexcept
            {
                return this->_config;
            }

        private:
            Engine::Entities::Config _config;
    };  // Configuration

}  // Components

#endif  // COMPONENTS_CONFIGURATIONS_HPP
