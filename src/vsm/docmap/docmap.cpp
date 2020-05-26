#include "vsm/docmap/docmap.h"
#include "util/funcutil.h"
#include "util/maputil.h"
#include "util/stringutil.h"
#include <cmath>

namespace vsm
{
    const std::string DocumentMap::DELIM_DOCMAP_L1 = "|";
    const std::string DocumentMap::DELIM_DOCMAP_L2_BEG = "START";
    const std::string DocumentMap::DELIM_DOCMAP_L2_END = "END";

    DocumentMap::DocumentMap() : _dmap(DMap()) {}

    DocumentMap::DocumentMap(DMap dmap) : _dmap(dmap) {}

    unsigned int DocumentMap::corpus_size() const noexcept
    {
        return _dmap.size();
    }

    double DocumentMap::vector_length(DocId docid) const noexcept
    {
        auto values = util::values(*_dmap.at(docid));
        auto squared = util::map(std::vector<Count>(values.begin(), values.end()),
                                 [](int i) { return (double)i * (double)i; });
        double sum = util::reduce(squared, 0.0,
                                  [](double x, double y) { return x + y; });
        return sqrt(sum);
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

    DocumentMap DocumentMap::from_stream(std::istream& in)
    {
        DMap dmap;

        bool inside = false;
        std::string docid;

        for (std::string line; std::getline(in, line);) {
            line = util::trim(line);
            if (line == DELIM_DOCMAP_L2_BEG) {
                inside = true;
            } else if (line == DELIM_DOCMAP_L2_END) {
                inside = false;
            } else if (inside) {
                auto elements = util::split(line, DELIM_DOCMAP_L1);
                auto term = elements[0];
                auto count = static_cast<unsigned int>(std::stoi(elements[1]));
                (*dmap[docid])[term] = count;
            } else {
                docid = line;
                auto ptr = std::make_shared<TermCountMap>();
                dmap[docid] = ptr;
            }
        }

        return DocumentMap(dmap);
    }

    void DocumentMap::writetofile(std::ostream& out)
    {
        for (const auto& [docid, termcountmap] : _dmap) {
            out << docid << "\n";
            out << DELIM_DOCMAP_L2_BEG << "\n";
            for (const auto& [term, count] : *termcountmap) {
                out << "\t" << term << DELIM_DOCMAP_L1 << count << "\n";
            }
            out << DELIM_DOCMAP_L2_END << "\n";
        }
    }

}
