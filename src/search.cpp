#include "vsm/vsmodel.h"
#include <fstream>
#include <getopt.h>
#include <iostream>
#include <sstream>

struct Arguments
{
    std::string FILENAME_POSTINGS;
    std::string FILENAME_DICTIONARY;
    std::string FILENAME_DOCUMENTS;
    std::string FILENAME_QUERIES;
};

Arguments getargs(int argc, char *argv[])
{
    Arguments ret = {"", "", "", ""};

    const char* const opts = "p:d:q:v:";
    std::string usage = "Usage: " + std::string(argv[0])
                        + " -d path/to/dictionary/file"
                        " -p path/to/postings/file"
                        " -v path/to/documents/file"
                        " -q path/to/queries/file";

    int P_PROCESSED = 0;
    int D_PROCESSED = 0;
    int Q_PROCESSED = 0;
    int V_PROCESSED = 0;

    while (1) {
        switch (getopt(argc, argv, opts)) {
        case 'p':
            ret.FILENAME_POSTINGS = std::string(optarg);
            P_PROCESSED++;
            continue;
        case 'd':
            ret.FILENAME_DICTIONARY = std::string(optarg);
            D_PROCESSED++;
            continue;
        case 'q':
            ret.FILENAME_QUERIES = std::string(optarg);
            Q_PROCESSED++;
            continue;
        case 'v':
            ret.FILENAME_DOCUMENTS = std::string(optarg);
            V_PROCESSED++;
            continue;
        default:
            throw std::invalid_argument(usage);
        case -1:
            break;
        }
        break;
    }

    if (D_PROCESSED != 1 || P_PROCESSED != 1 || Q_PROCESSED != 1 || V_PROCESSED != 1)
        throw std::invalid_argument(usage);

    return ret;
}

template<typename T>
std::string vectostr(std::vector<T> v)
{
    if (v.empty()) {
        return "[]";
    }

    std::stringstream ss;
    ss << "[" << v[0];
    for (size_t i = 1; i < v.size(); i++) {
        ss << ", " << v[i];
    }
    return ss.str() + "]";
}

int main(int argc, char *argv[])
{
    Arguments args;
    try {
        args = getargs(argc, argv);
    } catch (std::invalid_argument& ia) {
        std::cerr << ia.what() << "\n";
        exit(EXIT_FAILURE);
    }

    auto dict_stream = std::ifstream(args.FILENAME_DICTIONARY);
    auto plist_stream = std::ifstream(args.FILENAME_POSTINGS);
    auto doc_stream = std::ifstream(args.FILENAME_DOCUMENTS);

    auto model = vsm::VectorSpaceModel::of(dict_stream, plist_stream, doc_stream);

    std::ifstream queries(args.FILENAME_QUERIES);

    std::string query;
    while (std::getline(queries, query)) {
        std::vector<std::string> docids = model.cosine_similarity(query);
        std::cout << "[" << query << "] " << vectostr(docids) << "\n";
    }

    queries.close();
}
