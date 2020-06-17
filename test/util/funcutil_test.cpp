#include "catch2/catch.hpp"
#include "util/funcutil.h"
#include <list>
#include <set>
#include <vector>

template<typename T>    using Vector    = std::vector<T>;
template<typename T>    using Set       = std::set<T>;
template<typename T>    using List      = std::list<T>;

auto numbers = {1, 2, 3, 4, 5};

Vector<int> int_test_vector(numbers);
List<int> int_test_list(numbers);
Set<int> int_test_set(numbers);

TEST_CASE("fmap")
{
    SECTION("Non-empty vector") {

        SECTION("Change of type, different containers") {
            Vector<double> expected1({1.0, 2.0, 3.0, 4.0, 5.0});
            Vector<double> actual1 = util::fmap(int_test_vector, [](int i) {
                return static_cast<double>(i);
            });

            List<double> expected2({1.0, 2.0, 3.0, 4.0, 5.0});
            List<double> actual2 = util::fmap(int_test_list, [](int i) {
                return static_cast<double>(i);
            });

            Set<double> expected3({1.0, 2.0, 3.0, 4.0, 5.0});
            Set<double> actual3 = util::fmap(int_test_set, [](int i) {
                return static_cast<double>(i);
            });

            REQUIRE(expected1 == actual1);
        }

        SECTION("Arithmetic operation") {
            Vector<int> expected({7, 13, 23, 37, 55});
            Vector<int> actual = util::fmap(int_test_vector, [](int i) {
                return (2*i*i) + 5;
            });
            REQUIRE(expected == actual);
        }

        SECTION("Identity function") {
            Vector<int> expected({1, 2, 3, 4, 5});
            Vector<int> actual = util::fmap(int_test_vector, [](int i) {
                return i;
            });
            REQUIRE(expected == actual);
        }
    }

    SECTION("Empty vector") {
        Vector<int> v;
        Vector<int> actual = util::fmap(v, [](int i) {
            return i;
        });
        REQUIRE(actual.size() == 0);
    }
}

TEST_CASE("reduce")
{
    SECTION("Non-empty vector") {
        SECTION("Zero init value") {
            int expected = 15;
            int actual = util::reduce(int_test_vector, 0, [](int x, int y) {
            });
            REQUIRE(expected == actual);
        }

        SECTION("Non-zero init value") {
            int expected = 20;
            int actual = util::reduce(int_test_vector, 5, [](int x, int y) {
                return x + y;
            });
            REQUIRE(expected == actual);
        }

        SECTION("Empty map returns init") {
            int expected = 1;
            auto empty = std::vector<int>();
            int actual = util::reduce(empty, 1, [](int x, int y) {
                return x + y;
            });
            REQUIRE(actual == expected);
        }
    }
}
