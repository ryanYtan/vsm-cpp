#ifndef UTIL_MAPUTIL_H_INCLUDED
#define UTIL_MAPUTIL_H_INCLUDED
#include <map>
#include <set>

namespace util
{
    template<typename K, typename V, typename OutputIt>
    OutputIt
    keys(const std::map<K,V>& map, OutputIt result)
    {
        for (const auto& [key, val] : map) {
            *result = key;
            (void)++result;
        }
        return result;
    }

    template<typename K, typename V, typename OutputIt>
    OutputIt
    values(const std::map<K,V>& map, OutputIt result)
    {
        for (const auto& [key, val] : map) {
            *result = val;
            (void)++result;
        }
        return result;
    }

    template<typename K, typename V, typename OutputIt, typename PairMaker>
    OutputIt
    items(const std::map<K,V>& map, OutputIt result, PairMaker maker)
    {
        for (const auto& [key, val] : map) {
            *result = maker(key, val);
            (void)++result;
        }
        return result;
    }

    template<typename K, typename V, typename OutputIt>
    OutputIt
    common_keys(const std::map<K,V>& first, const std::map<K,V>& second,
                OutputIt result)
    {
        if (first.size() > second.size()) {
            for (const auto& [key, val] : second) {
                if (first.find(key) != first.end()) {
                    *result = key;
                    (void)++result;
                }
            }
        } else {
            for (const auto& [key, val] : first) {
                if (second.find(key) != second.end()) {
                    *result = key;
                    (void)++result;
                }
            }
        }
        return result;
    }

    template<typename K, typename V, typename OutputIt>
    OutputIt
    all_keys(const std::map<K,V>& first, const std::map<K,V>& second,
             OutputIt result)
    {
        std::set<K> all;
        for (const auto& [key, val] : first)  { all.insert(key); }
        for (const auto& [key, val] : second) { all.insert(key); }

        for (const auto& key : all) {
            *result = key;
            (void)++result;
        }
        return result;
    }
}

#endif
