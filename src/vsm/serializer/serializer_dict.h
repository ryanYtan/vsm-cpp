#ifndef VSM_SERIALIZER_SERIALIZER_DICT_H_INCLUDED
#define VSM_SERIALIZER_SERIALIZER_DICT_H_INCLUDED
#include "vsm/serializer/serializer.h"
#include "vsm/posindex/dictionary/dict.h"

namespace vsm
{
    class DictionarySerializer : Serializer<Dictionary>
    {
    public:
        DictionarySerializer();
        unsigned int serialize(Dictionary obj, OStream& output);
        Dictionary deserialize(IStream& input);
    };
}

#endif
