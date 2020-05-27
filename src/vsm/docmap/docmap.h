#ifndef VSM_DOCMAP_DOCMAP_H_INCLUDED
#define VSM_DOCMAP_DOCMAP_H_INCLUDED
#include "vsm/vsm_common.h"
#include <map>
#include <memory>

namespace vsm
{
    class DocumentMap
    {
    public:
        using TermCountMap = std::map<Term, Count>;
        using TermCountMapPtr = std::shared_ptr<TermCountMap>;
        using DMap = std::map<DocId, TermCountMapPtr>;
        using VectorPair = std::vector<std::pair<DocId,TermCountMapPtr>>;

        DocumentMap();
        DocumentMap(DMap dmap);

        unsigned int corpus_size() const noexcept;
        double vector_length(DocId docid) const;
        Count of(DocId docid, Term term) const;
        void insert(DocId docid, Term term);
        VectorPair items() const;

    private:
        DMap _dmap;
    };
}

#endif
