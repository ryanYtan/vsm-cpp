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
        REQUIRE(test_dict.get("a") == 100);
        REQUIRE(test_dict.get("d") == 400);
        REQUIRE_THROWS(test_dict.get("e"));
        REQUIRE_THROWS(test_dict_empty.get("a"));
    }

    SECTION("from_stream") {
        std::stringstream ss;
        ss << "a|100\n"
           << "b|200\n"
           << "c|300\n"
           << "d|400\n";
        auto actual = Dictionary::from_stream(ss);

        REQUIRE(actual.get("a") == test_dict.get("a"));
        REQUIRE(actual.get("b") == test_dict.get("b"));
        REQUIRE(actual.get("c") == test_dict.get("c"));
        REQUIRE(actual.get("d") == test_dict.get("d"));
        REQUIRE_THROWS(actual.get("e"));
    }
}
