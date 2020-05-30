#include "vsm/serializer/serializer_dict.h"
#include "util/stringutil.h"

namespace vsm
{
    constexpr auto DELIM = "|";

    DictionarySerializer::DictionarySerializer() {}

    unsigned int
    DictionarySerializer::serialize(Dictionary obj, OStream& output)
    {
        auto items = obj.items();
        std::string line;
        unsigned int bytes_written = 0;
        for (const auto& pair : items) {
            auto term = pair.first;
            auto offset = pair.second;
            line = term + DELIM + std::to_string(offset) + "\n";
            output << line;
            bytes_written += line.length();
        }
        return bytes_written;
    }

    Dictionary DictionarySerializer::deserialize(IStream& input)
    {
        Dictionary::Dict to_build;
        for (std::string s; std::getline(input, s);) {
            s = util::trim(s);
            std::vector<std::string> termoffset_pairs;
            util::split(std::back_inserter(termoffset_pairs), s, DELIM);
            auto term = termoffset_pairs[0];
            auto offset = static_cast<Offset>(std::stoi(termoffset_pairs[1]));
            to_build[term] = offset;
        }
        return Dictionary(to_build);
    }
}
