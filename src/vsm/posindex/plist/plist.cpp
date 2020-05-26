#include "vsm/posindex/plist/plist.h"
#include "util/funcutil.h"
#include "util/maputil.h"
#include "util/stringutil.h"

using VectorStr = std::vector<std::string>;

namespace vsm
{
    const std::string PostingList::SERIALIZE_DELIM_L1 = "|";
    const std::string PostingList::SERIALIZE_DELIM_L2 = ",";
    const std::string PostingList::SERIALIZE_DELIM_L3 = " ";

    PostingList::PostingList()
        : _plist(PMap())
    {
    }

    PostingList::PostingList(PMap plist)
        : _plist(plist)
    {
    }

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

    std::string PostingList::serialize() const
    {
        VectorStr plists;
        for (const auto &[docid, tuple] : _plist)
        {
            auto termfreq_str = std::to_string(tuple.get()->termfreq);
            auto positions_str = util::join(tuple.get()->positions,
                    PostingList::SERIALIZE_DELIM_L3);
            plists.push_back(docid
                    + PostingList::SERIALIZE_DELIM_L2 + termfreq_str
                    + PostingList::SERIALIZE_DELIM_L2 + positions_str);
        }
        return util::join(plists, PostingList::SERIALIZE_DELIM_L1);
    }

    PostingList PostingList::parse(const std::string& serialized)
    {
        PMap pmap;
        auto plists = util::split(serialized, PostingList::SERIALIZE_DELIM_L1);

        for (const auto& plist : plists) {
            auto components = util::split(plist, PostingList::SERIALIZE_DELIM_L2);

            auto docid = components[0];
            auto termfreq = static_cast<TermFreq>(std::stoi(components[1]));
            auto positions = util::split(components[2],
                    PostingList::SERIALIZE_DELIM_L3);
            auto poslist = util::map(positions, [](std::string s) {
                return static_cast<Position>(std::stoi(s));
            });

            pmap[docid] = std::make_shared<PostingListTuple>(PostingListTuple{
                termfreq, poslist
            });
        }

        return PostingList(pmap);
    }
}
