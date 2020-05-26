#ifndef VSM_BUILDER_INDEX_BUILDER_H_INCLUDED
#define VSM_BUILDER_INDEX_BUILDER_H_INCLUDED
#include "vsm/vsm_common.h"
#include "vsm/posindex/plist/plist.h"
#include "vsm/docmap/docmap.h"
#include <map>

namespace vsm
{
    class IndexBuilder
    {
    public:
        using TermPList = std::map<Term, PostingList>;

        IndexBuilder();

        void insert(DocId docid, Term term, Position position);

        void finalize(const std::string& ofile_dict,
                      const std::string& ofile_postings,
                      const std::string& ofile_documents);

    private:
        TermPList _builder_dict;
        DocumentMap _docmap;
    };
}

#endif
