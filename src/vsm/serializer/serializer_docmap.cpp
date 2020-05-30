#include "vsm/serializer/serializer_docmap.h"
#include "util/stringutil.h"

namespace vsm
{
    constexpr auto DELIM = "|";
    constexpr auto DELIM_OPENER = "START";
    constexpr auto DELIM_CLOSER = "END";

    DocumentMapSerializer::DocumentMapSerializer() {}

    unsigned int
    DocumentMapSerializer::serialize(DocumentMap obj, OStream& output)
    {
        unsigned int bytes_written = 0;

        auto pairs = obj.items();
        for (const auto& pair : pairs) {
            auto docid = pair.first;

            auto opener = docid + "\n" + DELIM_OPENER + "\n";
            output << opener;

            for (const auto& [term, count] : *pair.second) {
                auto termcount_line = term + DELIM + std::to_string(count) + "\n";
                output << termcount_line;
                bytes_written += termcount_line.length();
            }

            auto closer = std::string(DELIM_CLOSER) + "\n";
            output << closer;

            bytes_written += opener.length() + closer.length();
        }
        return bytes_written;
    }

    DocumentMap
    DocumentMapSerializer::deserialize(IStream& input)
    {
        DocumentMap::DMap dmap;

        bool inside = false;
        std::string docid;

        for (std::string s; std::getline(input, s);) {
            s = util::trim(s);
            if (s == DELIM_OPENER) {
                inside = true;
            } else if (s == DELIM_CLOSER) {
                inside = false;
            } else if (inside) {
                std::vector<std::string> termcount_pairs;
                util::split(std::back_inserter(termcount_pairs), s, DELIM);
                auto term = termcount_pairs[0];
                auto count = static_cast<Count>(std::stoi(termcount_pairs[1]));
                (*dmap[docid])[term] = count;
            } else {
                docid = s;
                auto ptr = std::make_shared<DocumentMap::TermCountMap>();
                dmap[docid] = ptr;
            }
        }
        return DocumentMap(dmap);
    }
}
