#include "catch2/catch.hpp"
#include "util/maputil.h"

using namespace util;

Map<String, int> test_map_empty;

Map<String, int> test_map({
    {"a", 1},
    {"b", 2},
    {"c", 3}
});

Map<String, int> test_map_2({
    {"c", 3},
    {"d", 4},
    {"e", 5}
});

Map<String, int> test_map_3({
    {"f", 6}
});

TEST_CASE("keys")
{
    SECTION("Non-empty map") {
        Set<String> expected = {"a", "b", "c"};
        auto actual = keys(test_map);
        REQUIRE(expected == actual);
    }

    SECTION("Empty map") {
        Set<String> expected;
        auto actual = keys(test_map_empty);
        REQUIRE(expected == actual);
    }
}

TEST_CASE("values")
{
    SECTION("Non-empty map") {
        Set<int> expected = {1, 2, 3};
        auto actual = values(test_map);
        REQUIRE(expected == actual);
    }

    SECTION("Empty map") {
        Set<int> expected;
        auto actual = values(test_map_empty);
        REQUIRE(expected == actual);
    }
}

TEST_CASE("items")
{
    SECTION("Non-empty map") {
        Vector<Pair<std::string, int>> expected({
            {"a", 1},
            {"b", 2},
            {"c", 3}
        });
        auto actual = items(test_map);
        REQUIRE(expected == actual);
    }

    SECTION("Empty map") {
        Vector<Pair<std::string, int>> expected;
        auto actual = items(test_map_empty);
        REQUIRE(expected == actual);
    }
}

TEST_CASE("common_keys")
{
    SECTION("Have common keys") {
        Set<String> expected = {"c"};
        auto actual = common_keys(test_map, test_map_2);
        REQUIRE(expected == actual);
    }

    SECTION("No common keys") {
        Set<String> expected;
        auto actual = common_keys(test_map, test_map_3);
        REQUIRE(expected == actual);
    }

    SECTION("Empty maps") {
        Set<String> expected;
        auto actual = common_keys(test_map_empty, test_map_empty);
        REQUIRE(expected == actual);
    }
}

TEST_CASE("all_keys")
{
    SECTION("Non-empty maps") {
        Set<String> expected({"a", "b", "c", "d", "e"});
        auto actual = all_keys(test_map, test_map_2);
        REQUIRE(expected == actual);
    }

    SECTION("One empty map") {
        Set<String> expected({"a", "b", "c"});
        auto actual = all_keys(test_map, test_map_empty);
        REQUIRE(expected == actual);
    }

    SECTION("Both empty maps") {
        Set<String> expected;
        auto actual = all_keys(test_map_empty, test_map_empty);
        REQUIRE(expected == actual);
    }
}
