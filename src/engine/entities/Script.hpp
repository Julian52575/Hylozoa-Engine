#ifndef ENTITIESSCRIPT_HPP
    #define ENTITIESSCRIPT_HPP

#include <string>

namespace Engine {
namespace Entities {

    class Script {
        public:
            Script(const std::string& path, const std::string& defaultBehaviorFun)
                : _defaultBehaviorFun(defaultBehaviorFun)
            {

            }
            ~Script()
            {

            }

            void setCurrentScript(const std::string& name)
            {

            }

        private:
            std::string _defaultBehaviorFun = "default";
            // lua handler i guess
    };

}  // namespace Entities
}  // namespace Engine

#endif  // ENTITIESSCRIPT_HPP
