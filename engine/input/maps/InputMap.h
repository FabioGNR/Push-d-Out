#pragma once

#include "AnalogMap.h"
#include <map>
#include <memory>

namespace engine {
namespace input {
    namespace maps {
        class InputMap {
        private:
            AnalogMap m_KBM{};
            std::map<int, AnalogMap> m_conList;

        public:
            AnalogMap& getMap(int id);
            AnalogMap& getKBM();
            void update();
        };
    }
}
}
