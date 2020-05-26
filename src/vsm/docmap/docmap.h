#ifndef VSM_DOCMAP_DOCMAP_H_INCLUDED
#define VSM_DOCMAP_DOCMAP_H_INCLUDED
#include "vsm/vsm_common.h"
#include <istream>
#include <map>
#include <memory>
#include <ostream>

namespace vsm
{
    class DocumentMap
    {
    public:
        using TermCountMap = std::map<Term, Count>;
        using TermCountMapPtr = std::shared_ptr<TermCountMap>;
        using DMap = std::map<DocId, TermCountMapPtr>;

        static const std::string DELIM_DOCMAP_L1;
        static const std::string DELIM_DOCMAP_L2_BEG;
        static const std::string DELIM_DOCMAP_L2_END;

        DocumentMap();
        DocumentMap(DMap);

        unsigned int corpus_size() const noexcept;
        double vector_length(DocId docid) const noexcept;
        void insert(DocId docid, Term term);

        static DocumentMap from_stream(std::istream& in);
        void writetofile(std::ostream& out);

    private:
        DMap _dmap;
    };
}

#endif
