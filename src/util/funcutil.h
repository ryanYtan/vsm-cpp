#ifndef UTIL_FUNCUTIL_H_INCLUDED
#define UTIL_FUNCUTIL_H_INCLUDED
#include <algorithm>

namespace util
{
    template<typename T,
             template <typename, typename...> typename Container,
             typename UnaryOperator,
             typename... Args>
    auto
    fmap(Container<T, Args...> con, UnaryOperator op)
            -> Container<decltype(op(std::declval<T>()))> // Container<op(T)>
    {
        using ReturnType = decltype(op(std::declval<T>()));

        Container<ReturnType> ret;

        if (con.empty()) {
            return ret;
        }

        auto ins = std::inserter(ret, ret.begin());
        std::transform(con.begin(), con.end(), ins, [&op](T t) { return op(t); });

        return ret;
    }

    template<typename T,
             template <typename, typename...> typename Container,
             typename BinaryOperator,
             typename... Args>
    auto
    reduce(Container<T, Args...> con, T init, BinaryOperator bop)
            -> T
    {
        if (con.empty()) {
            return init;
        }

        T ret = init;
        for (const auto& element : con) {
            ret = bop(ret, element);
        }

        return ret;
    }
}

#endif
