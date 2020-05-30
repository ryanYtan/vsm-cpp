#include "vsm/serializer/serializer_plist.h"
#include "util/stringutil.h"
#include "util/funcutil.h"

namespace vsm
{
    constexpr auto DELIM_L1 = "|";
    constexpr auto DELIM_L2 = ",";
    constexpr auto DELIM_L3 = " ";

    PostingListSerializer::PostingListSerializer() {}

    std::string _combine(const std::string& docid,
                         const TermFreq& termfreq,
                         const PositionList& positions)
    {
        return docid + DELIM_L2
                + std::to_string(termfreq) + DELIM_L2
                + util::join(positions, DELIM_L3);
    }

    unsigned int
    PostingListSerializer::serialize(PostingList obj, OStream& output)
    {
        if (obj.items().size() == 0) {
            return 0;
        }

        std::vector<std::string> plists;

        for (const auto& tuple : obj.items()) {
            std::string combined = _combine(tuple.docid, tuple.termfreq,
                                            tuple.positions);
            plists.push_back(combined);
        }

        auto outstring = util::join(plists, DELIM_L1);
        output << outstring << "\n";
        return outstring.length() + 1;
    }

    PostingList PostingListSerializer::deserialize(IStream& input)
    {
        PostingList::PMap pmap;
        std::string serialized;
        std::getline(input, serialized);
        serialized = util::trim(serialized);

        std::vector<std::string> plists;
        util::split(std::back_inserter(plists), serialized, DELIM_L1);

        for (const std::string& plist : plists) {
            std::vector<std::string> components;
            util::split(std::back_inserter(components), plist, DELIM_L2);

            auto docid = components[0];
            auto termfreq = static_cast<TermFreq>(std::stoi(components[1]));

            std::vector<std::string> positions;
            util::split(std::back_inserter(positions), components[2], DELIM_L3);

            auto poslist = util::fmap(positions, [](std::string s) {
                return static_cast<Position>(std::stoi(s));
            });

            pmap[docid] = std::make_shared<PostingListTuple>(PostingListTuple{
                termfreq, poslist
            });
        }
        return PostingList(pmap);
    }
}
