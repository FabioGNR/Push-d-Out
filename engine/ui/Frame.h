#pragma once
#include "components/Component.h"
#include <engine/input/maps/InputMap.h>
#include <memory>

namespace engine {
namespace ui {
    class Frame {
    public:
        explicit Frame(std::unique_ptr<Component> rootComponent)
            : m_rootComponent{ std::move(rootComponent) }
            , m_focusedComponent{}
            , m_activeComponent{ 0 }
        {
            m_focusedComponent = getNavigatableAt(m_activeComponent);
        }

        Frame(const Frame& other) = delete;
        Frame(Frame&& other)
        {
            this->m_rootComponent = std::move(other.m_rootComponent);
            this->m_focusedComponent = other.m_focusedComponent;
            this->m_activeComponent = other.m_activeComponent;
        }

        Frame& operator=(const Frame& other) = delete;
        Frame& operator=(Frame&& other)
        {
            if (this != &other) {
                this->m_rootComponent = std::move(other.m_rootComponent);
                this->m_focusedComponent = other.m_focusedComponent;
                this->m_activeComponent = other.m_activeComponent;
            }
            return *this;
        }

        void processInputEvent(engine::input::maps::InputMap& inputMap);
        void draw(IRenderer& renderer, common::Vector2D<int> screenSize) const;

    private:
        std::unique_ptr<Component> m_rootComponent;
        Component* m_focusedComponent;
        size_t m_activeComponent;
        Component* getNavigatableAt(size_t index) const;
        size_t getNavigatableComponentCount() const;
    };
}
}