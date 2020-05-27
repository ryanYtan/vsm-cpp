#include "vsm/builder/indexbuilder.h"
#include "vsm/serializer/serializer_dict.h"
#include "vsm/serializer/serializer_docmap.h"
#include "vsm/serializer/serializer_plist.h"
#include <fstream>

namespace vsm
{
    IndexBuilder::IndexBuilder()
        : _builder_dict(TermPList())
        , _docmap(DocumentMap())
    {}

    void IndexBuilder::insert(DocId docid, Term term, Position position)
    {
        _builder_dict[term].insert(docid, position);
        _docmap.insert(docid, term);
    }

    void IndexBuilder::build(const std::string& ofile_dict,
                             const std::string& ofile_postings,
                             const std::string& ofile_documents)
    {
        std::ofstream dstream(ofile_dict);
        std::ofstream pstream(ofile_postings);
        std::ofstream docstream(ofile_documents);

        PostingListSerializer pls;
        DictionarySerializer ds;
        DocumentMapSerializer dms;

        // create dictionary
        Dictionary::Dict termoffset_map;

        unsigned long long offset = 0;

        for (const auto& [term, plist] : _builder_dict) {
            termoffset_map[term] = offset;
            auto length = pls.serialize(plist, pstream);
            offset += length;
        }

        Dictionary d(termoffset_map);

        // serialize
        ds.serialize(d, dstream);
        dms.serialize(_docmap, docstream);
    }
}
