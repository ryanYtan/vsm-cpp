#include "catch2/catch.hpp"
#include "vsm/posindex/plist/plist_map.h"
#include "plist_test_common.h"
#include <sstream>

using namespace vsm;

TEST_CASE("Posting list mapper")
{
    PostingList::PMap pmap1({
        { "1", _create_tuple(2, {0, 1}) },
        { "2", _create_tuple(1, {0}) },
        { "3", _create_tuple(3, {1, 2, 3}) }
    });
    auto offset_1 = 0;
    std::string serialized_plist_1 = "1,2,0 1|2,1,0|3,3,1 2 3";
    PostingList test_plist_1(pmap1);

    PostingList::PMap pmap2({
        { "1", _create_tuple(2, {3, 4}) },
        { "2", _create_tuple(1, {2}) }
    });
    auto offset_2 = serialized_plist_1.length() + 1;
    std::string serialized_plist_2 = "1,2,3 4|2,1,2";
    PostingList test_plist_2(pmap2);


    std::stringstream ss;
    ss << serialized_plist_1 << "\n"
       << serialized_plist_2 << "\n";


    SECTION("at") {
        PostingListMapper actual(ss);
        REQUIRE(actual.at(offset_1) == test_plist_1);
        REQUIRE(actual.at(offset_2) == test_plist_2);
    }
}
