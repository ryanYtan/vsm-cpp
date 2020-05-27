#ifndef VSM_SERIALIZER_SERIALIZER_PLIST_H_INCLUDED
#define VSM_SERIALIZER_SERIALIZER_PLIST_H_INCLUDED
#include "vsm/serializer/serializer.h"
#include "vsm/posindex/plist/plist.h"

namespace vsm
{
    class PostingListSerializer : Serializer<PostingList>
    {
    public:
        PostingListSerializer();
        unsigned int serialize(PostingList obj, OStream& output);
        PostingList deserialize(IStream& input);
    };
}

#endif
