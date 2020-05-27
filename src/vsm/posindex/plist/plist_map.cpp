#include "vsm/posindex/plist/plist_map.h"
#include "vsm/serializer/serializer_plist.h"
#include "util/stringutil.h"

namespace vsm
{
    PostingListMapper::PostingListMapper(std::istream& plmap)
        : _plmap(plmap)
    {}

    PostingList PostingListMapper::at(Offset offset)
    {
        _plmap.seekg(offset, std::istream::beg);
        auto plist = PostingListSerializer().deserialize(_plmap);
        return plist;
    }
}
