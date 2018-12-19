#pragma once

#include <engine/graphics/IGraphicsElement.h>

namespace game::level::editor::ui {
class ISelectionScrollbar : public engine::IGraphicsElement {
public:
    ISelectionScrollbar() = default;

    virtual ~ISelectionScrollbar() = default;
    virtual void draw(const engine::IRenderer& renderer) const = 0;
    virtual const common::Vector2D<int>& position() const = 0;
    virtual void setPosition(const common::Vector2D<int>& position) = 0;

    virtual const common::Vector2D<int>& getSize() = 0;
    virtual void setSize(const common::Vector2D<int>& size) = 0;
};
}