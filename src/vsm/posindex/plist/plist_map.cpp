#include "vsm/posindex/plist/plist_map.h"
#include "util/stringutil.h"

namespace vsm
{
    PostingListMapper::PostingListMapper(std::istream& plmap)
        : _plmap(plmap)
    {}

    PostingList PostingListMapper::at(Offset offset)
    {
        _plmap.seekg(offset, std::istream::beg);
        std::string line;
        std::getline(_plmap, line);
        line = util::trim(line);
        _plmap.seekg(0, std::istream::beg); // reset seek
        return PostingList::parse(line);
    }
}
