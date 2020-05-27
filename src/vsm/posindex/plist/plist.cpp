#include "vsm/posindex/plist/plist.h"
#include "util/funcutil.h"
#include "util/maputil.h"
#include "util/stringutil.h"

using VectorStr = std::vector<std::string>;

namespace vsm
{
    PostingList::PostingList()
        : _plist(PMap())
    {}

    PostingList::PostingList(PMap plist)
        : _plist(plist)
    {}

    DocFreq PostingList::docfreq() const
    {
        return _plist.size();
    }

    TermFreq PostingList::termfreq(DocId docid) const
    {
        return _plist.at(docid).get()->termfreq;
    }

    PositionList PostingList::positions(DocId docid) const
    {
        return _plist.at(docid).get()->positions;
    }

    std::vector<PostingListItem> PostingList::items() const
    {
        std::vector<PostingListItem> ret;
        for (const auto& [docid, tuple] : _plist) {
            ret.push_back(PostingListItem{
                docid,
                (*tuple).termfreq,
                (*tuple).positions,
            });
        }
        return ret;
    }

    void PostingList::insert(DocId docid, Position position)
    {
        if (_plist.find(docid) == _plist.end()) {
            auto ptr = std::make_shared<PostingListTuple>();
            ptr->termfreq = 1;
            ptr->positions.push_back(position);
            _plist[docid] = ptr;
        } else {
            auto tup = _plist[docid].get();
            tup->termfreq += 1;
            tup->positions.push_back(position);
        }
    }

    bool operator==(const PostingList& lhs, const PostingList& rhs)
    {
        if (lhs._plist.size() != rhs._plist.size()) {
            return false;
        }

        for (const auto& [docid, tupleptr] : lhs._plist) {

            if (rhs._plist.find(docid) == rhs._plist.end()) {
                return false;
            }

            auto rhs_tupleptr = rhs._plist.at(docid);

            if ((*tupleptr).positions != (*rhs_tupleptr).positions
                    || (*tupleptr).termfreq != (*rhs_tupleptr).termfreq) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const PostingList& lhs, const PostingList& rhs)
    {
        return !(lhs == rhs);
    }
}
