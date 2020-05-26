#ifndef UTIL_STRINGUTIL_H_INCLUDED
#define UTIL_STRINGUTIL_H_INCLUDED
#include "util/util_common.h"
#include <sstream>

namespace util
{
    /**
     * @brief
     *
     * @tparam T
     * @param container
     * @param delim
     * @return String
     */
    template<typename T>
    String join(const Vector<T>& container, const String& delim = "")
    {
        if (container.empty()) {
            return "";
        }

        auto it = container.begin();

        std::stringstream ss;
        ss << *it;

        (void)++it;
        while (it != container.end()) {
            ss << delim << *it;
            (void)++it;
        }

        return ss.str();
    }

    /**
     * @brief
     *
     * @param s
     * @param delim
     * @return Vector<String>
     */
    Vector<String> split(const String& s, const String& delim = " ");

    /**
     * @brief
     *
     * @param s
     * @return String
     */
    String trim(const String& s);

    /**
     * @brief
     *
     * @param s
     * @return String
     */
    String casefold(const String& s);

    /**
     * @brief
     *
     * @param s
     * @return true
     * @return false
     */
    bool hasalnum(const String& s);

    /**
     * @brief
     *
     * @param s
     * @return String
     */
    String porterstem(const String& s);
}

#endif
