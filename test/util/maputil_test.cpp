#include "catch2/catch.hpp"
#include "util/maputil.h"

using namespace util;

template<typename K, typename V> using Map      = std::map<K,V>;
template<typename T>             using Set      = std::set<T>;
                                 using String   = std::string;

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
        Set<String> actual;
        keys(test_map, std::inserter(actual, actual.begin()));
        REQUIRE(expected == actual);
    }

    SECTION("Empty map") {
        Set<String> expected;
        Set<String> actual;
        keys(test_map_empty, std::inserter(actual, actual.begin()));
        REQUIRE(expected == actual);
    }
}

TEST_CASE("values")
{
    SECTION("Non-empty map") {
        Set<int> expected = {1, 2, 3};
        Set<int> actual;
        values(test_map, std::inserter(actual, actual.begin()));
        REQUIRE(expected == actual);
    }

    SECTION("Empty map") {
        Set<int> expected;
        Set<int> actual;
        values(test_map_empty, std::inserter(actual, actual.begin()));
        REQUIRE(expected == actual);
    }
}

TEST_CASE("items")
{
    auto pair_maker = [](std::string k, int v) {
        return std::make_pair(k, v);
    };

    SECTION("Non-empty map") {
        std::vector<std::pair<std::string, int>> expected({
            pair_maker("a", 1),
            pair_maker("b", 2),
            pair_maker("c", 3),
        });
        std::vector<std::pair<std::string, int>> actual;
        items(test_map, std::back_inserter(actual), pair_maker);
        REQUIRE(expected == actual);
    }

    SECTION("Empty map") {
        std::vector<std::pair<std::string, int>> expected;
        std::vector<std::pair<std::string, int>> actual;
        items(test_map_empty, std::back_inserter(actual), pair_maker);
        REQUIRE(expected == actual);
    }
}

TEST_CASE("common_keys")
{
    SECTION("Have common keys") {
        std::vector<std::string> expected({"c"});
        std::vector<std::string> actual;
        common_keys(test_map, test_map_2, std::back_inserter(actual));
        REQUIRE(expected == actual);
    }

    SECTION("No common keys") {
        std::vector<std::string> expected;
        std::vector<std::string> actual;
        common_keys(test_map, test_map_3, std::back_inserter(actual));
        REQUIRE(expected == actual);
    }

    SECTION("Empty maps") {
        std::vector<std::string> expected;
        std::vector<std::string> actual;
        common_keys(test_map_empty, test_map_empty, std::back_inserter(actual));
        REQUIRE(expected == actual);
    }
}

TEST_CASE("all_keys")
{
    SECTION("Non-empty maps") {
        std::vector<std::string> expected({"a", "b", "c", "d", "e"});
        std::vector<std::string> actual;
        all_keys(test_map, test_map_2, std::back_inserter(actual));

        std::vector<std::string> expected2({"a", "b", "c", "f"});
        std::vector<std::string> actual2;
        all_keys(test_map, test_map_3, std::back_inserter(actual2));
        REQUIRE(expected == actual);
        REQUIRE(expected2 == actual2);
    }

    SECTION("One empty map") {
        std::vector<std::string> expected({"a", "b", "c"});
        std::vector<std::string> actual;
        all_keys(test_map, test_map_empty, std::back_inserter(actual));
        REQUIRE(expected == actual);
    }

    SECTION("Both empty maps") {
        std::vector<std::string> expected;
        std::vector<std::string> actual;
        all_keys(test_map_empty, test_map_empty, std::back_inserter(actual));
        REQUIRE(expected == actual);
    }
}
