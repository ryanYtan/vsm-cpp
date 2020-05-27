#ifndef UTIL_MAPUTIL_H_INCLUDED
#define UTIL_MAPUTIL_H_INCLUDED
#include "util/util_common.h"
#include <map>
#include <set>

namespace util
{
    template<typename K, typename V>
    using Map = std::map<K,V>;
    template<typename T>
    using Set = std::set<T>;
    template<typename T1, typename T2>
    using Pair = std::pair<T1,T2>;

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
    Vector<Pair<K,V>> items(const Map<K,V>& map)
    {
        Vector<Pair<K,V>> items;
        for (const auto& [key, val] : map) {
            items.push_back(std::make_pair(key, val));
        }
        return items;
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
