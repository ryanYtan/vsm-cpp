#ifndef VSM_VSM_COMMON_H_INCLUDED
#define VSM_VSM_COMMON_H_INCLUDED
#include <string>
#include <vector>

namespace vsm
{
    using Count         = unsigned int;
    using Offset        = unsigned int;
    using Position      = unsigned int;
    using TermFreq      = unsigned int;
    using DocFreq       = unsigned int;
    using PositionList  = std::vector<Position>;
    using Term          = std::string;
    using DocId         = std::string;
}

#endif
