// Hylozoa Engine
#include <rengine/src/SparseArray.hpp>
#include <algorithm>

#include "hitbox.hpp"
#include "position.hpp"

namespace Components {

    void Hitbox::componentFunction(Rengine::ECS& ecs, Components::Hitbox& hitbox, Rengine::Entity& entity)
    {
        Rengine::SparseArray<Components::Hitbox>& hitboxs = ecs.getComponents<Components::Hitbox>();
        Rengine::SparseArray<Components::Position>& positions = ecs.getComponents<Components::Position>();
        std::optional<std::reference_wrapper<Position>> posWrapper = entity.getComponentNoExcept<Position>();
        
        if (posWrapper == std::nullopt) {
            return;
        }
        
        HitboxData ownHitboxSpecs;
        double ownHitboxStartX, ownHitboxStartY;
        
        posWrapper->get().get(ownHitboxStartX, ownHitboxStartY);
        hitbox.get(ownHitboxSpecs);
        
        double ownHitboxEndX = ownHitboxStartX + ownHitboxSpecs.hitboxSize.x;
        double ownHitboxEndY = ownHitboxStartY + ownHitboxSpecs.hitboxSize.y;
        
        for (Rengine::ECS::size_type index = Rengine::ECS::size_type(entity) + 1; index <= ecs.getHighestEntityId(); index++) {
            if (hitboxs[index].has_value() == false || positions[index].has_value() == false) {
                continue;
            }

            HitboxData hitboxSpecs;
            hitboxs[index]->get(hitboxSpecs);

            if (std::find(ownHitboxSpecs.collidingLayers.begin(), ownHitboxSpecs.collidingLayers.end(), hitboxSpecs.layer) == ownHitboxSpecs.collidingLayers.end()) {
                continue;
            }
            
            double hitboxStartX, hitboxStartY;

            positions[index]->get(hitboxStartX, hitboxStartY);

            double hitboxEndX = hitboxStartX + hitboxSpecs.hitboxSize.x;
            double hitboxEndY = hitboxStartY + hitboxSpecs.hitboxSize.y;
            
            if (!((ownHitboxStartX <= hitboxEndX && ownHitboxEndX >= hitboxStartX) &&
            (ownHitboxStartY <= hitboxEndY && ownHitboxEndY >= hitboxStartY))) {
                std::cout << "No collision detected" << std::endl;
                continue;
            }

            std::cout << "Collison id: " << int(entity) << " and " << index << std::endl;
        }

    }

} // namespace Components
