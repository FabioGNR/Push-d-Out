#pragma once

#include <engine/exceptions/ResourceNotFoundException.h>

#include <algorithm>
#include <memory>
#include <vector>

namespace common {
template <typename K, typename V, size_t C>
class LimitedResourceCache {
    size_t m_insertPosition = 0;
    std::vector<std::pair<K, V>> m_cache;

public:
    void addResource(const K& k, V v)
    {

        if (m_cache.size() < m_insertPosition + 1) {
            m_cache.push_back({ k, std::move(v) });
        } else {
            m_cache[m_insertPosition] = { k, std::move(v) };
        }
        m_insertPosition++;
        if (m_insertPosition >= C) {
            m_insertPosition = 0;
        }
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
