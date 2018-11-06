#pragma once

#include <string>

namespace engine {
namespace sound {
    class Sound {
        std::string m_soundPath;

    public:
        explicit Sound(std::string soundPath);

        const std::string& soundPath() const;
        void setSoundPath(std::string soundPath);
    };
} // end namespace sound
} // end namespace engine
