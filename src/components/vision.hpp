#ifndef COMPONENTSVISION_HPP
    #define COMPONENTSVISION_HPP

#include <cstdint>
#include <functional>
#include <sched.h>
#include <vector>

#include "src/engine/entities/Script.hpp"

namespace Components {
    struct VisionConfig {
        std::uint64_t vision_strength_meter = 10;
        struct VisionScript {
            std::uint64_t target_id;
            std::string fun;
            int priority = 0;
        };
        std::vector<VisionScript> vision_scripts;
    };

    class Vision {
        public:
            Vision() = default; // default constructor for sparse array
            Vision(const VisionConfig& con)
            {
                this->_visionStrengthMeter = con.vision_strength_meter;
            }
            ~Vision() = default;

            void updateScript(Engine::Entities::Script& script)
            {

            }

        private:
            std::uint64_t _visionStrengthMeter = 10;
            std::vector<VisionConfig::VisionScript> _visionScripts;
    };  // Vision
}  // Components
#endif  // COMPONENTSVISION_HPP
