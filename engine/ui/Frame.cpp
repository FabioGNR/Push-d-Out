#include "Frame.h"
#include <ui/components/ComponentPanel.h>

namespace engine {
namespace ui {
    using namespace engine::input;

    void Frame::processInputEvent(maps::InputMap& inputMap)
    {
        //TODO: use proper mapping for this instead of hardcoded W and S
        // if navigation key(s)
        bool navigate = inputMap.hasState(Keys::W, States::PRESSED) || inputMap.hasState(Keys::S, States::PRESSED);
        navigate = inputMap.hasState(AnalogKeys::CON_LEFTSTICK_Y, States::PRESSED) ? true : navigate;
        if (navigate) {
            size_t navigatableComponentCount = getNavigatableComponentCount();
            bool goForward = inputMap.hasState(Keys::S, States::PRESSED);
            goForward = inputMap.getValue(AnalogKeys::CON_LEFTSTICK_Y) > 0 ? true : goForward;
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
        } else if (m_focusedComponent != nullptr) {
            m_focusedComponent->processInputEvent(inputMap);
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

    Component* Frame::getNavigatableAt(size_t index) const
    {
        auto* rootPanel = dynamic_cast<ComponentPanel*>(m_rootComponent.get());
        if (rootPanel != nullptr) {
            auto newFocusedComponent = rootPanel->getNavigatableAt(index);
            return newFocusedComponent;
        }

        return m_rootComponent.get();
    }
}
}
