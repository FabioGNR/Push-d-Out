#include <engine/exceptions/ResourceNotFoundException.h>
#include <fstream>
#include "SpriteReader.h"

namespace game{
    namespace sprite {
        json SpriteReader::readJSON(const std::string &jsonFileName) {
            std::ifstream i(jsonFileName);
            if (!i.good()) {
                throw ResourceNotFoundException(jsonFileName);
            }
            json j;
            i >> j;
            return j;
        }
        std::map<std::string, Animation> SpriteReader::getAnimationsFromJSON(const json &j) {
            AnimationList animationList = j;
            std::vector<Animation> animations = animationList.animations;

            std::map<std::string, Animation> result;

            for (auto curAnim : animations) {
                std::pair<std::string, Animation> pair(curAnim.name, curAnim);
                result.insert(pair);
            }

            return result;
        }

    }
}



