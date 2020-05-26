#include "catch2/catch.hpp"
#include "vsm/posindex/plist/plist_map.h"
#include <sstream>

using namespace vsm;

TEST_CASE("Posting list mapper")
{
    std::string serialized_plist_1 = "1,2,0 1|2,1,0|3,3,1 2 3";
    auto offset_1 = 0;
    std::string serialized_plist_2 = "1,2,3 4|2,1,2";
    auto offset_2 = serialized_plist_1.length() + 1;

    std::stringstream ss;
    ss << serialized_plist_1 << "\n"
       << serialized_plist_2 << "\n";

    SECTION("at") {
        PostingListMapper actual(ss);
        REQUIRE(actual.at(offset_1).serialize() == serialized_plist_1);
        REQUIRE(actual.at(offset_2).serialize() == serialized_plist_2);
    }
}
