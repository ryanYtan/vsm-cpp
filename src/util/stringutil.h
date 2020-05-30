#ifndef UTIL_STRINGUTIL_H_INCLUDED
#define UTIL_STRINGUTIL_H_INCLUDED
#include <sstream>

namespace util
{
    template<typename T,
             template<typename, typename...> typename Container,
             typename... Args>
    std::string
    join(const Container<T>& con, const std::string& delim = " ")
    {
        if (con.empty()) {
            return "";
        }
        std::stringstream ss;
        size_t i = 1;
        for (const auto& s : con) {
            if (i == con.size()) {
                ss << s;
            } else {
                ss << s << delim;
            }
            i++;
        }
        return ss.str();
    }

    // Adapted with minor modifications: https://stackoverflow.com/a/57346888/10966389
    template<typename OutputIt>
    OutputIt
    split(OutputIt result, const std::string& s, const std::string& delim = " ")
    {
        if (s.empty()) {
            *result = "";
            return result;
        }

        size_t found = s.find(delim);
        size_t start_index = 0;

        while (found != std::string::npos) {
            std::string temp(s.begin() + start_index, s.begin() + found);

            *result = temp;
            (void)++result;

            start_index = found + delim.size();
            found = s.find(delim, start_index);
        }

        *result = std::string(s.begin() + start_index, s.end());
        return result;
    }

    inline bool
    is_trimmable(char c)
    {
        return !isalnum(c);
    }

    std::string
    trim(const std::string& s);

    std::string
    casefold(const std::string& s);

    bool
    hasalnum(const std::string& s);

    std::string
    porterstem(const std::string& s);
}

#endif
