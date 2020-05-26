#pragma once
#include "vsm/vsm_common.h"
#include "vsm/posindex/dictionary/dict.h"
#include "vsm/posindex/plist/plist_map.h"
#include "vsm/docmap/docmap.h"

namespace vsm
{
    class VectorSpaceModel
    {
    public:
        static VectorSpaceModel of(std::istream& dict_stream,
                                   std::istream& postings_stream,
                                   std::istream& doc_stream);



        std::vector<DocId> cosine_similarity(std::string query);
        unsigned int corpus_size() const noexcept;
        static double logfw(int tf, int base = 10);
        static double loginvf(int df, int n, int base = 10);
        static double tfidf(int tf, int df, int n, int base = 10);

    private:
        Dictionary _dict;
        PostingListMapper _plistmap;
        DocumentMap _dmap;

        VectorSpaceModel(Dictionary dict, PostingListMapper plmap, DocumentMap dmap);
    };
}
