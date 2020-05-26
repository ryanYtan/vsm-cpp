#include "catch2/catch.hpp"
#include "vsm/posindex/plist/plist.h"
#include <iostream>

using namespace vsm;

PostingList::PTuplePtr _create_tuple(DocFreq df, std::initializer_list<Position> pos)
{
    return std::make_shared<PostingListTuple>(
        PostingListTuple{df, pos}
    );
}

TEST_CASE("Posting list")
{
    PostingList::PMap pmap({
        {
            "1", std::make_shared<PostingListTuple>(PostingListTuple{3, {0, 1, 2}})
        },
        {
            "2", std::make_shared<PostingListTuple>(PostingListTuple{4, {2, 3, 4, 5}})
        },
        {
            "3", std::make_shared<PostingListTuple>(PostingListTuple{2, {1, 4}})
        }
    });

    const DocFreq expected_df = 3;
    const TermFreq expected_tf_1 = 3;
    const TermFreq expected_tf_2 = 4;
    const TermFreq expected_tf_3 = 2;
    const PositionList expected_poslist_1 = {0, 1, 2};
    const PositionList expected_poslist_2 = {2, 3, 4, 5};
    const PositionList expected_poslist_3 = {1, 4};
    const std::string expected_serialized = "1,3,0 1 2|2,4,2 3 4 5|3,2,1 4";

    PostingList test_plist(pmap);

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

    SECTION("insert") {
        REQUIRE(actual.docfreq() == expected_df);
        REQUIRE(actual.termfreq("1") == expected_tf_1);
        REQUIRE(actual.termfreq("2") == expected_tf_2);
        REQUIRE(actual.termfreq("3") == expected_tf_3);
        REQUIRE(actual.positions("1") == expected_poslist_1);
        REQUIRE(actual.positions("2") == expected_poslist_2);
        REQUIRE(actual.positions("3") == expected_poslist_3);
    }

    SECTION("serialized") {
        REQUIRE(actual.serialize() == expected_serialized);
    }

    SECTION("parse") {
        PostingList actual2 = PostingList::parse(expected_serialized);
        REQUIRE(actual2.docfreq() == expected_df);
        REQUIRE(actual2.termfreq("1") == expected_tf_1);
        REQUIRE(actual2.termfreq("2") == expected_tf_2);
        REQUIRE(actual2.termfreq("3") == expected_tf_3);
        REQUIRE(actual2.positions("1") == expected_poslist_1);
        REQUIRE(actual2.positions("2") == expected_poslist_2);
        REQUIRE(actual2.positions("3") == expected_poslist_3);
    }
}
