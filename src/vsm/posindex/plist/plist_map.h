#ifndef VSM_POSINDEX_PLIST_PLIST_MAP_H_INCLUDED
#define VSM_POSINDEX_PLIST_PLIST_MAP_H_INCLUDED
#include "vsm/vsm_common.h"
#include "vsm/posindex/plist/plist.h"
#include <istream>

namespace vsm
{
    class PostingListMapper
    {
    public:
        PostingListMapper(std::istream& plmap);
        PostingList at(Offset offset);
    private:
        std::istream& _plmap;
    };
}

#endif
