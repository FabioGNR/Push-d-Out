#include "Frame.h"
#include <ui/components/ComponentPanel.h>
namespace engine {
namespace ui {
    void Frame::processInputEvent()
    {
        //TODO: keyevent parameter, pass it through
        // if navigation key(s)
        bool navigate = true; //TODO: determine based on input key used
        if (navigate) {
            size_t navigatableComponentCount = getNavigatableComponentCount();
            bool goForward = false; //TODO: go back or go forward? check pressed key
            if (goForward) {
                m_activeComponent++;
                if (m_activeComponent >= navigatableComponentCount) {
                    m_activeComponent = 0;
                }
            } else {
                if (m_activeComponent == 0) {
                    m_activeComponent = navigatableComponentCount - 1;
                } else {
                    m_activeComponent--;
                }
            }
            m_focusedComponent = getNavigatableAt(m_activeComponent);
        } else {
            m_focusedComponent->processInputEvent();
        }
    }

    void Frame::draw(IRenderer& renderer, common::Vector2D<int> screenSize) const
    {
        if (m_rootComponent == nullptr) {
            return;
        }
        DrawContext context{ screenSize, renderer, m_focusedComponent };
        m_rootComponent->draw(context);
    }

    size_t Frame::getNavigatableComponentCount() const
    {
        auto* rootPanel = dynamic_cast<ComponentPanel*>(m_rootComponent.get());
        if (rootPanel != nullptr) {
            return rootPanel->countNavigatableChildren();
        }
        return 1;
    }

    std::shared_ptr<Component> Frame::getNavigatableAt(size_t index) const
    {
        auto* rootPanel = dynamic_cast<ComponentPanel*>(m_rootComponent.get());
        if (rootPanel != nullptr) {
            auto newFocusedComponent = rootPanel->getNavigatableAt(index);
            return newFocusedComponent;
        }

        return m_rootComponent;
    }
}
}
