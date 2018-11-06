#pragma once

#include <engine/exceptions/ResourceNotFoundException.h>

#include <algorithm>
#include <memory>
#include <vector>

namespace common {
template <typename K, typename V>
class ResourceCache {
    std::vector<std::pair<K, V>> m_cache;

public:
    void addResource(const K& k, V v)
    {
        m_cache.push_back({ k, std::move(v) });
    }

    bool hasResource(const K& k)
    {
        return m_cache.end() != std::find_if(m_cache.begin(), m_cache.end(), [&](const auto& pair) {
            return k == pair.first;
        });
    }

    const V& getResource(const K& k) const
    {
        const auto it = std::find_if(m_cache.begin(), m_cache.end(), [&](const auto& pair) {
            return k == pair.first;
        });

        if (it == m_cache.cend()) {
            throw ResourceNotFoundException("cache");
        }

        return (*it).second;
    }
};
} // end namespace common
