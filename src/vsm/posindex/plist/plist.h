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

        static const std::string SERIALIZE_DELIM_L1;
        static const std::string SERIALIZE_DELIM_L2;
        static const std::string SERIALIZE_DELIM_L3;

        PostingList();
        PostingList(PMap plist);

        DocFreq docfreq() const;
        TermFreq termfreq(DocId docid) const;
        PositionList positions(DocId docid) const;

        std::vector<PostingListItem> items() const;

        void insert(DocId docid, Position position);

        std::string serialize() const;
        static PostingList parse(const std::string& serialized);

    private:
        PMap _plist;
    };
}

#endif
