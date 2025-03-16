// julian.bottiglione@epitech.eu
// Create a Entity from a config path

#ifndef ENTITYFACTORY_HPP
    #define ENTITYFACTORY_HPP

#include "Entity.hpp"

namespace Engine {
namespace Entities {
    class EntityFactory {
        public:
            EntityFactory() = default;
            ~EntityFactory() = default;

            Entity create(const std::string& path)
            {

            }
    };
}  // namespace Entities
}  // namespace Engine

#endif  // ENTITYFACTORY_HPP
