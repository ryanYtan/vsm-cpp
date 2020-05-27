#ifndef VSM_POSINDEX_PLIST_PLIST_H_INCLUDED
#define VSM_POSINDEX_PLIST_PLIST_H_INCLUDED
#include "vsm/vsm_common.h"
#include <map>
#include <memory>
#include <tuple>

namespace vsm
{
    struct PostingListTuple
    {
        TermFreq termfreq;
        PositionList positions;
    };

    struct PostingListItem
    {
        DocId docid;
        TermFreq termfreq;
        PositionList positions;
    };

    class PostingList
    {
    public:
        using PTuplePtr = std::shared_ptr<PostingListTuple>;
        using PMap = std::map<DocId, PTuplePtr>;

        PostingList();
        PostingList(PMap plist);

        DocFreq docfreq() const;
        TermFreq termfreq(DocId docid) const;
        PositionList positions(DocId docid) const;
        std::vector<PostingListItem> items() const;
        void insert(DocId docid, Position position);

        friend bool operator==(const PostingList& lhs, const PostingList& rhs);
        friend bool operator!=(const PostingList& lhs, const PostingList& rhs);

    private:
        PMap _plist;
    };
}

#endif
