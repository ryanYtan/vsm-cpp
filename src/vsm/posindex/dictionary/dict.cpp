#include "vsm/posindex/dictionary/dict.h"
#include "util/stringutil.h"
#include "util/maputil.h"
#include <istream>

namespace vsm
{
    Dictionary::Dictionary(Dict dict)
        : _dict(dict)
    {}

    Count Dictionary::vocabulary_size() const noexcept
    {
        return _dict.size();
    }

    Offset Dictionary::offset_of(Term term) const
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

    Dictionary::VectorPairs Dictionary::items() const
    {
        return util::items(_dict);
    }
}
