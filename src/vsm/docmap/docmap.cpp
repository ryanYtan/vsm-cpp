#include "vsm/docmap/docmap.h"
#include "util/funcutil.h"
#include "util/maputil.h"
#include "util/stringutil.h"
#include <cmath>

namespace vsm
{
    DocumentMap::DocumentMap()
        : _dmap(DMap())
    {}

    DocumentMap::DocumentMap(DMap dmap)
        : _dmap(dmap)
    {}

    unsigned int DocumentMap::corpus_size() const noexcept
    {
        return _dmap.size();
    }

    double DocumentMap::vector_length(DocId docid) const
    {
        auto values = util::values(*_dmap.at(docid));
        auto as_vector = std::vector<Count>(values.begin(), values.end());
        auto squared = util::map(as_vector, [](int i) { return (double)i * i; });
        double sum = util::reduce(squared, 0.0, [](double x, double y) {
            return x + y;
        });
        return sqrt(sum);
    }

    Count DocumentMap::of(DocId docid, Term term) const
    {
        auto ptr = _dmap.at(docid);
        return (*ptr).at(term);
    }

    void DocumentMap::insert(DocId docid, Term term)
    {
        if (_dmap.find(docid) == _dmap.end()) {
            auto ptr = std::make_shared<TermCountMap>();
            (*ptr)[term] = 1;
            _dmap[docid] = ptr;
        } else {
            (*_dmap[docid])[term] += 1;
        }
    }

    DocumentMap::VectorPair DocumentMap::items() const
    {
        DocumentMap::VectorPair ret;
        for (const auto& [docid, ptr] : _dmap) {
            ret.push_back(std::make_pair(docid, ptr));
        }
        return ret;
    }
}
