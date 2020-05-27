#include "catch2/catch.hpp"
#include "vsm/posindex/plist/plist.h"
#include "plist_test_common.h"
#include <iostream>

using namespace vsm;

TEST_CASE("Posting list")
{
    PostingList::PMap pmap({
        { "1", _create_tuple(3, {0, 1, 2}) },
        { "2", _create_tuple(4, {2, 3, 4, 5}) },
        { "3", _create_tuple(2, {1, 4}) }
    });
    PostingList test_plist(pmap);

    SECTION("equality") {
        PostingList::PMap pmap2({
            { "1", _create_tuple(3, {0, 1, 2}) },
            { "2", _create_tuple(4, {2, 3, 4, 5}) },
            { "3", _create_tuple(2, {1, 4}) }
        });
        PostingList actual(pmap2);
        REQUIRE(actual == test_plist);

        PostingList::PMap pmap3({
            { "1", _create_tuple(3, {0, 1, 2}) },
            { "2", _create_tuple(4, {2, 3, 4, 5}) },
            { "3", _create_tuple(3, {1, 4, 5}) }
        });
        PostingList actual2(pmap3);
        REQUIRE(actual2 != test_plist);
    }

    SECTION("insert") {
        PostingList actual;
        actual.insert("1", 0);
        actual.insert("1", 1);
        actual.insert("1", 2);
        actual.insert("2", 2);
        actual.insert("2", 3);
        actual.insert("2", 4);
        actual.insert("2", 5);
        actual.insert("3", 1);
        actual.insert("3", 4);
        REQUIRE(actual == test_plist);
    }
}
