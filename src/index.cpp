#include "util/stringutil.h"
#include "vsm/builder/indexbuilder.h"
#include <glob.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>
#include <getopt.h>

struct Arguments
{
    std::string PATH_TO_TRAINING_DATA;  // -i
    std::string FILENAME_POSTINGS;      // -p
    std::string FILENAME_DICTIONARY;    // -d
    std::string FILENAME_DOCUMENTS;     // -v
};

Arguments getargs(int argc, char *argv[])
{
    Arguments ret = {"", "", "", ""};

    const char* const opts = "i:p:d:v:";
    std::string usage = "Usage:"
                        " " + std::string(argv[0])
                        + " -i path/to/training/data"
                        " -d path/to/dictionary/file"
                        " -p path/to/postings/file"
                        " -v path/to/documents/file";

    int I_PROCESSED = 0;
    int P_PROCESSED = 0;
    int D_PROCESSED = 0;
    int V_PROCESSED = 0;

    while (1) {
        switch (getopt(argc, argv, opts)) {
        case 'i':
            ret.PATH_TO_TRAINING_DATA = std::string(optarg);
            I_PROCESSED++;
            continue;
        case 'p':
            ret.FILENAME_POSTINGS = std::string(optarg);
            P_PROCESSED++;
            continue;
        case 'd':
            ret.FILENAME_DICTIONARY = std::string(optarg);
            D_PROCESSED++;
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

    if (I_PROCESSED != 1 || P_PROCESSED != 1 || D_PROCESSED != 1 || V_PROCESSED != 1)
        throw std::invalid_argument(usage);

    return ret;
}

std::vector<std::string> getfilepaths(const std::string& pattern)
{
    std::vector<std::string> filenames;

    glob_t glob_result;
    if (glob(pattern.c_str(), GLOB_TILDE, NULL, &glob_result) != 0) {
        throw std::invalid_argument("bad pattern");
    }

    for (size_t i = 0; i < glob_result.gl_pathc; i++) {
        std::string filename(glob_result.gl_pathv[i]);
        filenames.push_back(filename);
    }

    globfree(&glob_result);

    return filenames;
}

std::vector<std::string> tokenize(const std::string& text)
{
    auto tokens = util::split(text, " ");

    std::vector<std::string> result;

    for (const auto& s : tokens) {
        if (!util::hasalnum(s))
            continue;
        auto processed = util::porterstem(util::casefold(util::trim(s)));
        result.push_back(processed);
    }
    return result;
}

std::string readfile(const std::string& filename)
{
    std::ifstream ifs(filename);

    std::string text;
    std::string tmp;
    while (std::getline(ifs, tmp)) {
        text += tmp;
    }

    // remove newlines, replace with spaces
    for (char& c : text) {
        switch (c) {
        case '\n':
        case '\t':
        case '\r':
            c = ' ';
        default:
            break;
        }
    }

    ifs.close();
    return text;
}

int main(int argc, char *argv[])
{
    vsm::IndexBuilder builder;

    Arguments args;

    try {
        args = getargs(argc, argv);
    } catch (const std::invalid_argument& ia) {
        std::cerr << ia.what() << "\n";
        exit(EXIT_FAILURE);
    }

    auto files = getfilepaths(args.PATH_TO_TRAINING_DATA + "*");

    for (size_t i = 0; i < files.size(); i++) {
        std::string filepath = files[i];
        std::string docid = filepath.substr(args.PATH_TO_TRAINING_DATA.length());
        std::string text = readfile(filepath);
        int position = 0;
        for (const auto& s : tokenize(text)) {
            builder.insert(docid, s, position++);
        }
        printf("\rOn %zu of %zu", i + 1, files.size());
    }
    printf("\n");

    builder.build(args.FILENAME_DICTIONARY, args.FILENAME_POSTINGS,
                  args.FILENAME_DOCUMENTS);
}
