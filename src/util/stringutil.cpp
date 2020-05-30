#include "util/stringutil.h"
#include "porterstemmer.h"
#include <algorithm>

namespace util
{
    std::string
    trim(const std::string& s)
    {
        size_t front = 0;
        size_t back = s.length() - 1;

        while (front < s.length() && is_trimmable(s[front])) {
            front++;
        }

        while (back >= 0 && is_trimmable(s[back])) {
            back--;
        }

        return s.substr(front, back - front + 1);
    }

    std::string
    casefold(const std::string& s)
    {
        std::string ret;
        std::transform(s.begin(), s.end(), std::back_inserter(ret), ::tolower);
        return ret;
    }

    bool
    hasalnum(const std::string& s)
    {
        for (const char& c: s) {
            if (isalnum(c)) {
                return true;
            }
        }
        return false;
    }

    std::string
    porterstem(const std::string& s)
    {
        char* cstr = const_cast<char*>(s.c_str());
        int len = stem(cstr, 0, s.length() - 1);
        std::string ret;
        for (int i = 0; i <= len; i++) {
            ret += cstr[i];
        }
        return ret;
    }
}
