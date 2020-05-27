#ifndef VSM_SERIALIZER_SERIALIZER_DOCMAP_H_INCLUDED
#define VSM_SERIALIZER_SERIALIZER_DOCMAP_H_INCLUDED
#include "vsm/serializer/serializer.h"
#include "vsm/docmap/docmap.h"

namespace vsm
{
    class DocumentMapSerializer : Serializer<DocumentMap>
    {
    public:
        DocumentMapSerializer();
        unsigned int serialize(DocumentMap obj, OStream& output);
        DocumentMap deserialize(IStream& input);
    };
}

#endif
