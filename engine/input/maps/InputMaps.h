#pragma once

#include "InputMap.h"
#include <map>
#include <memory>

namespace engine {
namespace input {
    namespace maps {
        class InputMaps {
        private:
            InputMap m_KBM{};
            std::map<int, InputMap> m_conList;

        public:
            InputMap& getMap(int id);
            InputMap& getKBM();
            void update();
        };
    }
}
}
