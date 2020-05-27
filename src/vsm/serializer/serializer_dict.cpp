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
            auto term_offset = util::split(s, DELIM);
            auto term = term_offset[0];
            auto offset = static_cast<Offset>(std::stoi(term_offset[1]));
            to_build[term] = offset;
        }
        return Dictionary(to_build);
    }
}
