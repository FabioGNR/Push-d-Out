#pragma once
#include "components/Component.h"
#include <memory>

namespace engine {
namespace ui {
    class Frame {
    public:
        explicit Frame(const std::shared_ptr<Component>& rootComponent)
            : m_rootComponent{ rootComponent }
            , m_focusedComponent{ rootComponent }
            , m_activeComponent{ 0 }
        {
            m_focusedComponent = getNavigatableAt(m_activeComponent);
        }

        void processInputEvent();
        void draw(UIRenderer& renderer, common::Vector2D screenSize) const;

    private:
        std::shared_ptr<Component> m_rootComponent;
        std::shared_ptr<Component> m_focusedComponent;
        size_t m_activeComponent;
        std::shared_ptr<Component> getNavigatableAt(size_t index) const;
        size_t getNavigatableComponentCount() const;
    };
}
}