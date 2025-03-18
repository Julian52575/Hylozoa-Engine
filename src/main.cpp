//

#include <functional>
#include <rengine/RengineGraphics.hpp>
#include <rengine/src/ECS.hpp>
#include <rengine/src/Entity.hpp>
#include <rengine/src/Graphics/GraphicManager.hpp>
#include <rengine/src/Graphics/UserInputManager.hpp>
#include <rengine/src/Graphics/WindowSpecs.hpp>
#include <rengine/src/Rng/Rng.hpp>

#include "engine/world/World.hpp"
#include "src/components/configuration.hpp"
#include "src/components/position.hpp"
#include "src/components/sprite.hpp"
#include "src/components/vision.hpp"
#include "src/components/hitbox.hpp"
#include "src/engine/LoggingManager.hpp"
#include "src/engine/options/options.hpp"
#include "src/lib/Singleton.hpp"


void initECS() __attribute__ ((constructor));
void initECS()
{
    Lib::Singleton<Rengine::ECS>::getInstance().registerComponent<Components::Position>();
    Lib::Singleton<Rengine::ECS>::getInstance().registerComponent<Components::Sprite>();
    Lib::Singleton<Rengine::ECS>::getInstance().registerComponent<Components::Vision>();
    Lib::Singleton<Rengine::ECS>::getInstance().registerComponent<Components::Hitbox>();
    Lib::Singleton<Rengine::ECS>::getInstance().registerComponent<Components::Configuration>();
    Lib::Singleton<Rengine::ECS>::getInstance().setComponentFunction<Components::Hitbox>(Components::Hitbox::componentFunction);
    std::function<void(Rengine::Entity&)> onCreateFun =
        [](Rengine::Entity& en) {
            Lib::Singleton<Engine::LoggingManager>::getInstance().logTime();
            Lib::Singleton<Engine::LoggingManager>::getInstance() << "Creating entity #" << Rengine::ECS::size_type(en) << "\n";
            return;
        };
    /*std::function<void(Rengine::Entity&)> onDestroyFun =
        [](Rengine::Entity& en) {
            Lib::Singleton<Engine::LoggingManager>::getInstance().logTime();
            Lib::Singleton<Engine::LoggingManager>::getInstance() << "Destroying entity #" << Rengine::ECS::size_type(en) << "\n";
        };
    */
    Lib::Singleton<Rengine::ECS>::getInstance().setOnEntityCreationFunction(onCreateFun);
    //Lib::Singleton<Rengine::ECS>::getInstance().setOnEntityRemovalFunction(onDestroyFun);
}

void initWindow() __attribute__ ((constructor));
void initWindow()
{
    Rengine::Graphics::WindowSpecs specs;

    specs.options.isFullscreen = false;
    specs.options.isBorderless = false;
    specs.options.isResizable = true;
    Rengine::Graphics::GraphicManagerSingletone::get().createWindow(specs);
}

void handleInput(void)
{
    Rengine::Graphics::GraphicManagerSingletone::get().getWindow()->pollInput();
    auto &manager = Rengine::Graphics::GraphicManagerSingletone::get().getWindow()->getInputManager();

    for (auto& it : manager) {
        switch (it.type) {
            // Window close
            case (Rengine::Graphics::UserInputTypeWindowClosed):
                Rengine::Graphics::GraphicManagerSingletone::get().getWindow()->close();
                return;

                case (Rengine::Graphics::UserInputTypeKeyboardCharPressed):
                    // V for vision diplay

                    if (it.data.keyboardChar == 'a') {
                        if (Lib::Singleton<Engine::Options::Debug>::getInstance().showVision == true) {
                            Lib::Singleton<Engine::Options::Debug>::getInstance().showVision = false;
                            Lib::Singleton<Engine::LoggingManager>::getInstance().logTime();
                            Lib::Singleton<Engine::LoggingManager>::getInstance() << "Disabled vision debug circle.\n";
                        } else {
                            Lib::Singleton<Engine::Options::Debug>::getInstance().showVision = true;
                            Lib::Singleton<Engine::LoggingManager>::getInstance().logTime();
                            Lib::Singleton<Engine::LoggingManager>::getInstance() << "Enabled vision debug circle.\n";
                        }
                    }
                    break;


            default:
                break;
        }
    }
    Rengine::Graphics::GraphicManagerSingletone::get().getWindow()->getInputManager().clear();
}

int main(int ac, char * const *argv)
{
    if (ac != 2) {
        std::cout << "Usage: ./machin <world_config.json>" << std::endl;
        return 84;
    }
    Engine::World world = Engine::World(argv[1]);

    while (Rengine::Graphics::GraphicManagerSingletone::get().getWindow()->isOpen()) {
        // Component function
        Lib::Singleton<Rengine::ECS>::getInstance().runComponentFunction<Components::Hitbox>();

        // Render
        world.render();
        Rengine::Graphics::GraphicManagerSingletone::get().getWindow()->render();

        handleInput();
    }
    return 0;
}
