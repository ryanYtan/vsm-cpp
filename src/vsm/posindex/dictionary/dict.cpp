#include "vsm/posindex/dictionary/dict.h"
#include "util/stringutil.h"
#include <istream>

namespace vsm
{
    const std::string Dictionary::SERIALIZE_DELIM_L1 = "|";

    Dictionary::Dictionary()
        : _dict()
    {
    }

    Dictionary::Dictionary(Dict dict)
        : _dict(dict)
    {
    }

    Count Dictionary::vocabulary_size() const noexcept
    {
        return _dict.size();
    }

    Offset Dictionary::get(Term term) const
    {
        return _dict.at(term);
    }

    bool Dictionary::has(std::initializer_list<Term> terms) const noexcept
    {
        for (const auto& term : terms) {
            if (_dict.find(term) == _dict.end()) {
                return false;
            }
        }
        return true;
    }

    Dictionary Dictionary::from_stream(std::istream& lines)
    {
        Dict to_build;
        for (std::string s; std::getline(lines, s);) {
            s = util::trim(s);
            auto term_offset = util::split(s, Dictionary::SERIALIZE_DELIM_L1);
            auto term = term_offset[0];
            auto offset = static_cast<Offset>(std::stoi(term_offset[1]));
            to_build[term] = offset;
        }
        return Dictionary(to_build);
    }
}
