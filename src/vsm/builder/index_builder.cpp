#include "vsm/builder/index_builder.h"
#include "vsm/posindex/dictionary/dict.h"
#include <fstream>

namespace vsm
{
    IndexBuilder::IndexBuilder()
        : _builder_dict(std::map<Term, PostingList>()),
          _docmap(DocumentMap())
    {}

    void IndexBuilder::insert(DocId docid, Term term, Position position)
    {
        _builder_dict[term].insert(docid, position);
        _docmap.insert(docid, term);
    }

    void IndexBuilder::finalize(const std::string& ofile_dict,
                                const std::string& ofile_postings,
                                const std::string& ofile_documents)
    {
        std::ofstream dout(ofile_dict);
        std::ofstream pout(ofile_postings);
        std::ofstream docout(ofile_documents);

        Dictionary::Dict final_dict;

        // write to postings file and create dictionary
        Offset offset = 0;
        for (const auto& [term, plist] : _builder_dict) {
            std::string serialized_ln = plist.serialize() + "\n";
            pout << serialized_ln;
            final_dict[term] = offset;
            offset += serialized_ln.length();
        }

        // write to dictionary file
        for (const auto& [term, offset] : final_dict) {
            std::string serialized_ln = term + Dictionary::SERIALIZE_DELIM_L1
                                        + std::to_string(offset) + "\n";
            dout << serialized_ln;
        }

        // write to documents
        _docmap.writetofile(docout);
    }
}
