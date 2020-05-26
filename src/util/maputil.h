#ifndef UTIL_MAPUTIL_H_INCLUDED
#define UTIL_MAPUTIL_H_INCLUDED
#include "util/util_common.h"
#include <map>
#include <set>

namespace util
{
    template<typename K, typename V> using Map = std::map<K,V>;
    template<typename T> using Set = std::set<T>;

    template<typename K, typename V>
    Set<K> keys(const Map<K,V>& map)
    {
        Set<K> keys;
        for (const auto& [key, val] : map) {
            keys.insert(key);
        }
        return keys;
    }

    template<typename K, typename V>
    Set<V> values(const Map<K,V>& map)
    {
        Set<V> values;
        for (const auto& [key, val] : map) {
            values.insert(val);
        }
        return values;
    }

    template<typename K, typename V>
    Set<K> common_keys(const Map<K,V>& first, const Map<K,V>& second)
    {
        Set<K> common;
        if (first.size() > second.size()) {
            for (const auto& [key, val] : second) {
                if (first.find(key) != first.end()) {
                    common.insert(key);
                }
            }
        } else {
            for (const auto& [key, val] : first) {
                if (second.find(key) != second.end()) {
                    common.insert(key);
                }
            }
        }
        return common;
    }

    template<typename K, typename V>
    Set<K> all_keys(const Map<K,V>& first, const Map<K,V>& second)
    {
        Set<K> all;
        for (const auto& [key, val] : first) { all.insert(key); }
        for (const auto& [key, val] : second) { all.insert(key); }
        return all;
    }
}

#endif
