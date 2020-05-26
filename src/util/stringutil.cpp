#include "util/stringutil.h"
#include "porterstemmer.h"
#include <algorithm>

namespace util
{
    // Adapted with minor modifications: https://stackoverflow.com/a/57346888/10966389
    Vector<String> split(const String& s, const String& delim)
    {
        if (s.empty()) {
            return Vector<String>({""});
        }

        size_t found = s.find(delim);
        size_t start_index = 0;

        Vector<String> ret;

        while (found != std::string::npos) {
            String temp(s.begin() + start_index, s.begin() + found);

            ret.push_back(temp);

            start_index = found + delim.size();
            found = s.find(delim, start_index);
        }

        ret.push_back(String(s.begin() + start_index, s.end()));

        return ret;
    }

    static
    bool _is_trimmable(char c)
    {
        return !isalnum(c);
    }

    String trim(const String& s)
    {
        size_t front = 0;
        size_t back = s.length() - 1;

        while (front < s.length() && _is_trimmable(s[front])) {
            front++;
        }

        while (back >= 0 && _is_trimmable(s[back])) {
            back--;
        }

        return s.substr(front, back - front + 1);
    }

    String casefold(const String& s)
    {
        std::string ret;
        std::transform(s.begin(), s.end(), std::back_inserter(ret), ::tolower);
        return ret;
    }

    bool hasalnum(const String& s)
    {
        for (const char& c: s) {
            if (isalnum(c)) {
                return true;
            }
        }
        return false;
    }

    String porterstem(const String& s)
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
