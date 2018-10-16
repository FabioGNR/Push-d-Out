#include "Keymap.h"

namespace engine {
namespace input {
    bool Keymap::isKeyPressed(engine::input::Keys key)
    {
        return m_map.find(key) != m_map.end();
    }

    bool Keymap::isKeyPressed()
    {
        return !m_map.empty();
    }

    void Keymap::setKey(std::shared_ptr<events::IControlEvent> event)
    {
        m_map.insert(std::pair<Keys, std::shared_ptr<events::IControlEvent>>(event->getValue(), event));
    }
}
}
