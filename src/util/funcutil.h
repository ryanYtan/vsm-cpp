#ifndef UTIL_FUNCUTIL_H_INCLUDED
#define UTIL_FUNCUTIL_H_INCLUDED
#include "util/util_common.h"

namespace util
{
    template<typename T, typename UnaryOperator>
    auto map(Vector<T> vec, UnaryOperator uop)
            -> Vector<decltype(uop(std::declval<T>()))>
    {
        using ReturnType = decltype(uop(std::declval<T>()));

        if (vec.empty()) {
            return Vector<ReturnType>();
        }

        Vector<ReturnType> ret;
        for (const T& element : vec) {
            ReturnType mapped = uop(element);
            ret.push_back(mapped);
        }
        return ret;
    }

    template<typename T, typename BinaryOperator>
    T reduce(Vector<T> vec, T identity, BinaryOperator bop)
    {
        if (vec.empty()) {
            return identity;
        }
        T ret = identity;
        for (size_t i = 1; i < vec.size(); i++) {
            ret = bop(vec[i], ret);
        }
        return ret;
    }
}

#endif
