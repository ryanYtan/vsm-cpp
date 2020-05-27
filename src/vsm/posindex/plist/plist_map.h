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
        PostingListMapper(std::shared_ptr<std::istream> plmap_ptr);
        PostingList at(Offset offset);
    private:
        std::istream& _plmap;
    };
}

#endif
