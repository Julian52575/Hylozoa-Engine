//

#include <rengine/RengineGraphics.hpp>
#include <rengine/src/ECS.hpp>
#include <rengine/src/Graphics/GraphicManager.hpp>
#include <rengine/src/Graphics/UserInputManager.hpp>
#include <rengine/src/Graphics/WindowSpecs.hpp>

#include "engine/world/World.hpp"
#include "src/components/position.hpp"
#include "src/components/sprite.hpp"
#include "src/components/vision.hpp"
#include "src/components/hitbox.hpp"
#include "src/lib/Singleton.hpp"


void initECS() __attribute__ ((constructor));
void initWindow() __attribute__ ((constructor));

void initECS()
{
    Lib::Singleton<Rengine::ECS>::getInstance().registerComponent<Components::Position>();
    Lib::Singleton<Rengine::ECS>::getInstance().registerComponent<Components::Sprite>();
    Lib::Singleton<Rengine::ECS>::getInstance().registerComponent<Components::Vision>();

    Lib::Singleton<Rengine::ECS>::getInstance().registerComponent<Components::Hitbox>();
    Lib::Singleton<Rengine::ECS>::getInstance().setComponentFunction<Components::Hitbox>(Components::Hitbox::componentFunction);
}

void initWindow()
{
    Rengine::Graphics::WindowSpecs specs;

    specs.options.isFullscreen = false;
    specs.options.isBorderless = false;
    Rengine::Graphics::GraphicManagerSingletone::get().createWindow(specs);
}

int main(int ac, char * const *argv)
{
    if (ac != 2) {
        std::cout << "Usage: ./machin <world_config.json>" << std::endl;
        return 84;
    }
    Engine::World world = Engine::World(argv[1]);

    while (Rengine::Graphics::GraphicManagerSingletone::get().getWindow()->isOpen()) {
        world.render();
        Rengine::Graphics::GraphicManagerSingletone::get().getWindow()->render();
        Rengine::Graphics::GraphicManagerSingletone::get().getWindow()->pollInput();
        Lib::Singleton<Rengine::ECS>::getInstance().runComponentFunction<Components::Hitbox>();
        if (Rengine::Graphics::GraphicManagerSingletone::get().getWindow()->getInputManager().receivedInput(
        Rengine::Graphics::UserInputType::UserInputTypeWindowClosed)) {
            Rengine::Graphics::GraphicManagerSingletone::get().getWindow()->close();
        }
    }
    return 0;
}
