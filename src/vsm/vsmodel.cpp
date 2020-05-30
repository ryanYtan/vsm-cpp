#include "vsm/vsmodel.h"
#include "vsm/vmap/vmap.h"
#include "util/stringutil.h"
#include "vsm/serializer/serializer_dict.h"
#include "vsm/serializer/serializer_docmap.h"
#include <cmath>

namespace vsm
{
    VectorSpaceModel::VectorSpaceModel(Dictionary dict,
                                       PostingListMapper plmap,
                                       DocumentMap dmap)
        : _dict(dict), _plistmap(plmap), _dmap(dmap)
    {}

    VectorSpaceModel VectorSpaceModel::of(std::istream& dict_stream,
                                          std::istream& postings_stream,
                                          std::istream& doc_stream)
    {
        DictionarySerializer ds;
        auto dict = ds.deserialize(dict_stream);

        auto pmap = PostingListMapper(postings_stream);

        DocumentMapSerializer dms;
        auto dmap = dms.deserialize(doc_stream);

        return VectorSpaceModel(dict, pmap, dmap);
    }

    double VectorSpaceModel::logfw(int tf, int base)
    {
        if (tf == 0) {
            return 0;
        }
        return 1 + (log(tf) / log(base));
    }

    double VectorSpaceModel::loginvf(int df, int n, int base)
    {
        if (df == 0) {
            return 0;
        }
        return log(static_cast<double>(n) / df) / log(base);
    }

    double VectorSpaceModel::tfidf(int tf, int df, int n, int base)
    {
        return logfw(tf, base) * loginvf(df, n, base);
    }

    std::vector<DocId> VectorSpaceModel::cosine_similarity(std::string query) {
        std::vector<std::string> tokenized_query;
        util::split(std::back_inserter(tokenized_query), query, " ");

        auto qvector = VectorMap<Term>::vectorise(
            tokenized_query.begin(), tokenized_query.end(),
            [](std::string s) {
                return util::porterstem(s);
            },
            [](double v) {
                return v;
            }
        );

        using Score = double;
        std::map<DocId, Score> scores;

        for (const auto& [term, count] : qvector.getmap()) {
            if (!_dict.has({term})) {
                continue;
            }

            auto offset = _dict.offset_of(term);
            auto term_plist = _plistmap.at(offset);

            auto tf_tq = VectorSpaceModel::logfw(count);
            auto tf_idf = VectorSpaceModel::loginvf(term_plist.docfreq(),
                                                    _dmap.corpus_size());

            auto wtq = tf_tq * tf_idf;

            for (const auto& tuple : term_plist.items()) {
                auto docid = tuple.docid;
                auto termfreq = tuple.termfreq;

                auto wtd = VectorSpaceModel::logfw(termfreq);

                if (scores.find(docid) == scores.end()) {
                    scores[docid] = 0;
                }
                scores[docid] += wtd * wtq;
            }
        }

        // normalize
        for (auto& [docid, score] : scores) {
            score /= _dmap.vector_length(docid);
        }

        // get top 10 documents
        std::vector<DocId> result;

        std::vector<std::pair<DocId, Score>> tmp;
        for (const auto& [docid, score] : scores) {
            tmp.push_back({docid, score});
        }

        std::sort(tmp.begin(), tmp.end(), [](auto &left, auto& right) {
            return left.second > right.second; // sort in reverse
        });

        for (size_t i = 0; i < 10 && i < tmp.size(); i++) { // hardcoded
            result.push_back(tmp[i].first);
        }

        return result;
    }
}
