#ifndef COMPONENTS_HITBOX_HPP
    #define COMPONENTS_HITBOX_HPP

#include <rengine/src/Graphics/Vector.hpp>
#include <rengine/src/ECS.hpp>
#include <rengine/src/SparseArray.hpp>

namespace Components {

    struct HitboxData {
        Rengine::Graphics::vector2D<unsigned int> hitboxSize;
        std::string layer;
        std::vector<std::string> collidingLayers;

        HitboxData& operator=(const HitboxData& other) {
            if (this != &other) {
                hitboxSize.x = other.hitboxSize.x;
                hitboxSize.y = other.hitboxSize.y;
                layer = other.layer;
                collidingLayers = other.collidingLayers;
            }

            return *this;
        }
    };

    class Hitbox {
        public:
            Hitbox() = default;
            Hitbox(const HitboxData &specs) { _specs = specs; };
            ~Hitbox() = default;

            inline void get(HitboxData &specs) const noexcept
            {
                specs.hitboxSize.x = _specs.hitboxSize.x;
                specs.hitboxSize.y = _specs.hitboxSize.y;
                specs.layer = _specs.layer;
                specs.collidingLayers = _specs.collidingLayers;
            }

            static void componentFunction(Rengine::ECS& ecs, Components::Hitbox& hitbox, Rengine::Entity& entity);

            private:
            HitboxData _specs;
        };  // Hitbox
}  // Components

#endif  // COMPONENTS_HITBOX_HPP
