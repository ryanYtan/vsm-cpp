#include "catch2/catch.hpp"
#include "vsm/posindex/dictionary/dict.h"
#include <sstream>

using namespace vsm;

TEST_CASE("Dictionary")
{
    Dictionary::Dict dict({
        {"a", 100},
        {"b", 200},
        {"c", 300},
        {"d", 400}
    });
    Dictionary::Dict dict_empty;

    Dictionary test_dict(dict);
    Dictionary test_dict_empty(dict_empty);

    SECTION("vocabulary_size") {
        REQUIRE(test_dict.vocabulary_size() == dict.size());
        REQUIRE(test_dict_empty.vocabulary_size() == dict_empty.size());
    }

    SECTION("has") {
        REQUIRE(test_dict.has({"a"}) == true);
        REQUIRE(test_dict.has({"a", "b", "c"}) == true);
        REQUIRE(test_dict.has({"a", "b", "c", "d", "e"}) == false);
        REQUIRE(test_dict.has({"e"}) == false);
    }

    SECTION("get") {
        REQUIRE(test_dict.offset_of("a") == 100);
        REQUIRE(test_dict.offset_of("d") == 400);
        REQUIRE_THROWS(test_dict.offset_of("e"));
        REQUIRE_THROWS(test_dict_empty.offset_of("a"));
    }
}
