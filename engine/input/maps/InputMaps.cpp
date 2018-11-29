#include "InputMaps.h"

namespace engine {
namespace input {
    namespace maps {
        InputMap& InputMaps::getKBM()
        {
            return m_KBM;
        }

        InputMap& InputMaps::getMap(const int id)
        {
            if (id == -1) {
                return m_KBM;
            }

            if (m_conList.find(id) == m_conList.end()) {
                m_conList.insert({ id, InputMap() });
            }

            return m_conList[id];
        }

        void InputMaps::update()
        {
            m_KBM.update();
            auto it = m_conList.begin();
            while (it != m_conList.end()) {
                it++->second.update();
            }
        }
    }
}
}