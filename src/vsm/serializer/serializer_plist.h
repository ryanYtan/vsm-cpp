#include "vsm/serializer/serializer.h"
#include "vsm/posindex/dictionary/dict.h"

namespace vsm
{
    template<typename Dictionary>
    class DictionarySerializer : Serializer<Dictionary>
    {
    public:
        PostingListSerializer();
        ~PostingListSerializer();
    };
}
