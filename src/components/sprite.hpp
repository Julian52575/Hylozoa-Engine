//
#ifndef COMPONENTS_SPRITE_HPP
    #define COMPONENTS_SPRITE_HPP

#include "src/components/position.hpp"
#include <rengine/src/Graphics/Vector.hpp>
#include <string>
#include <rengine/src/Graphics/ASprite.hpp>
#include <rengine/src/Graphics/GraphicManager.hpp>
#include <rengine/src/Graphics/SpriteSpecs.hpp>

namespace Components {
    class Sprite {
        public:
            Sprite() = default;  // default constructor for sparse_array
            Sprite(const std::string& texturePath)
            {
                Rengine::Graphics::SpriteSpecs specs;

                specs.texturePath = texturePath;
                this->_sprite = Rengine::Graphics::GraphicManagerSingletone::get().createSprite(specs);
            }
            ~Sprite() = default;
            void render(const Components::Position& posComponent)
            {
                double x = 0;
                double y = 0;

                posComponent.get(x, y);
                Rengine::Graphics::GraphicManagerSingletone::get().addToRender(this->_sprite, {(float) x, (float) y});
            }

        private:
            std::shared_ptr<Rengine::Graphics::ASprite> _sprite = nullptr;
    };  // Sprite
}  // Components

#endif  // COMPONENTS_SPRITE_HPP
