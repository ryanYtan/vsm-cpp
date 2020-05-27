#ifndef VSM_DICTIONARY_DICT_H_INCLUDED
#define VSM_DICTIONARY_DICT_H_INCLUDED
#include "vsm/vsm_common.h"
#include <map>

namespace vsm
{
    class Dictionary
    {
    public:
        using Dict = std::map<Term, Offset>;
        using VectorPairs = std::vector<std::pair<Term, Offset>>;

        Dictionary(Dict dict);

        Count vocabulary_size() const noexcept;
        Offset offset_of(Term term) const;
        bool has(std::initializer_list<Term> terms) const noexcept;
        VectorPairs items() const;

    private:
        Dict _dict;
    };
}

#endif
