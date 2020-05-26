#include "catch2/catch.hpp"
#include "util/funcutil.h"

TEST_CASE("map")
{
    SECTION("Non-empty vector") {
        util::Vector<int> test_vector({1, 2, 3, 4, 5});

        SECTION("Change of type") {
            util::Vector<double> expected({1.0, 2.0, 3.0, 4.0, 5.0});
            util::Vector<double> actual = util::map(test_vector,
                [](int i) {
                    return static_cast<double>(i);
                }
            );
            REQUIRE(expected == actual);
        }

        SECTION("Arithmetic operation") {
            util::Vector<int> expected({7, 13, 23, 37, 55});
            util::Vector<int> actual = util::map(test_vector,
                [](int i) {
                    return (2*i*i) + 5;
                }
            );
            REQUIRE(expected == actual);
        }

        SECTION("Identity function") {
            util::Vector<int> expected({1, 2, 3, 4, 5});
            util::Vector<int> actual = util::map(test_vector,
                [](int i) { return i; }
            );
            REQUIRE(expected == actual);
        }
    }

    SECTION("Empty vector") {
        util::Vector<int> v;

        util::Vector<int> actual = util::map(v,
            [](int i) { return i; }
        );

        REQUIRE(actual.size() == 0);
    }
}
