#include "SpriteBuilder.h"
#include "../sprite/reader/SpriteReader.h"

namespace game {
    namespace builders{

        std::map<std::string, components::SpriteComponent> SpriteBuilder::build() const {
            json j = game::sprite::SpriteReader::readJSON(jsonFile);
            auto animations = game::sprite::SpriteReader::getAnimationsFromJSON(j);

            std::map<std::string, components::SpriteComponent> result;

            for(const auto &curAnimPair : animations) {
                auto& cur = curAnimPair.second;

                if(cur.frameCount == 1) {
                    sprite::SpriteResource sprite{spriteSheetPath, cur.topLeft, cur.frameSize, cur.offset};
                    result.insert(std::pair<std::string, components::SpriteComponent>(cur.name, components::SpriteComponent(sprite)));
                } else if(cur.frameCount > 1) {
                    std::vector<sprite::SpriteResource> sprites;
                    for(int i = 0; i < cur.frameCount; i++) {
                        common::Vector2D<int> position{cur.topLeft.x + i*cur.frameSize.x, cur.topLeft.y};
                        sprite::SpriteResource sprite{spriteSheetPath, position, cur.frameSize, cur.offset};
                        sprites.push_back(sprite);
                    }
                    result.insert(std::pair<std::string, components::SpriteComponent>(cur.name, components::SpriteComponent(sprites, cur.frameCount, cur.frameTime)));
                }
            }

            return result;
        }
    }
}