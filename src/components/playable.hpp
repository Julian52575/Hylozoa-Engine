//
#ifndef COMPONENTS_PLAYABLE_HPP
    #define COMPONENTS_PLAYABLE_HPP

#include "src/components/velocity.hpp"
#include <rengine/Rengine.hpp>
#include <rengine/src/Graphics/GraphicManager.hpp>
#include <rengine/src/Graphics/UserInputManager.hpp>

namespace Components {

    class Playable {
        public:
            Playable() = default;
            ~Playable() = default;
            static void componentFunction(Rengine::ECS& ecs, Components::Playable& playable, Rengine::Entity& entity)
            {
                bool update = false;
                Components::Velocity& velocity = entity.getComponent<Components::Velocity>();

                for (auto &input : Rengine::Graphics::GraphicManagerSingletone::get().getWindow()->getInputManager()) {
                    if (input.type == Rengine::Graphics::UserInputTypeKeyboardSpecialPressed) {
                        if (input.data.keyboardSpecial == Rengine::Graphics::UserInputKeyboardSpecialArrowRIGHT) {
                            velocity.getX() += 0.5;
                            update = true;
                        } else if (input.data.keyboardSpecial == Rengine::Graphics::UserInputKeyboardSpecialArrowLEFT) {
                            velocity.getX() -= 0.5;
                            update = true;
                        } else if (input.data.keyboardSpecial == Rengine::Graphics::UserInputKeyboardSpecialArrowUP) {
                            velocity.getY() -= 0.5;
                            update = true;
                        }
                    }
                }
                if (update == true) {
                    velocity.cap(5.0);
                }
            }
    };  // Playable

}  // Components

#endif  // COMPONENTS_PLAYABLE_HPP
