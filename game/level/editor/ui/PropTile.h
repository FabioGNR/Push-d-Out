
#include "ITile.h"
#include "TileSet.h"
#include "TileSpriteSelectionScrollbar.h"

#include <engine/common/Vector2D.h>
#include <engine/graphics/drawable/RectangleShape.h>
#include <engine/graphics/drawable/Sprite.h>
#include <engine/graphics/drawable/Surface.h>

#include <memory>

namespace game::level::editor::ui {
class PropTile : public ITile {

public:
    PropTile(const common::Vector2D<int>& position, const common::Vector2D<int>& size);
    ~PropTile() override = default;

    void draw(const engine::IRenderer& renderer) const override;
    void setPosition(const common::Vector2D<int>& position) override;
};
}
