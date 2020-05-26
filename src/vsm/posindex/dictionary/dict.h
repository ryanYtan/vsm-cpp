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

        static const std::string SERIALIZE_DELIM_L1;

        Dictionary();
        Dictionary(Dict dict);

        Count vocabulary_size() const noexcept;
        Offset get(Term term) const;
        bool has(std::initializer_list<Term> terms) const noexcept;

        static Dictionary from_stream(std::istream& lines);

    private:
        Dict _dict;
    };
}

#endif
