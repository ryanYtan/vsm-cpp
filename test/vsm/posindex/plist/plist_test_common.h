#ifndef TEST_VSM_POSINDEX_PLIST_PLIST_TEST_COMMMON_H_INCLUDED
#define TEST_VSM_POSINDEX_PLIST_PLIST_TEST_COMMMON_H_INCLUDED
#include "vsm/posindex/plist/plist.h"

using namespace vsm;

inline PostingList::PTuplePtr _create_tuple(DocFreq df, std::initializer_list<Position> pos)
{
    return std::make_shared<PostingListTuple>(
        PostingListTuple{df, pos}
    );
}

#endif
