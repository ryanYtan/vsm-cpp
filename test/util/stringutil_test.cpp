#include "catch2/catch.hpp"
#include "util/stringutil.h"

TEST_CASE("join")
{
    util::String TEST_STRING_1 = "aaa";
    util::String TEST_STRING_2 = "bbb ccc";
    util::String TEST_STRING_3 = "dddeee fff";
    util::String DELIM = " / ";

    SECTION("Non-empty vector") {
        SECTION("no delimiter") {
            util::Vector<util::String> test_input({
                TEST_STRING_1, TEST_STRING_2, TEST_STRING_3
            });

            util::String actual = util::join(test_input);
            util::String expected = TEST_STRING_1 + TEST_STRING_2 + TEST_STRING_3;
            REQUIRE(actual == expected);
        }
        SECTION("with delimiter") {
            util::Vector<util::String> test_input({
                TEST_STRING_1, TEST_STRING_2, TEST_STRING_3
            });

            util::String actual = util::join(test_input, DELIM);
            util::String expected = TEST_STRING_1
                    + DELIM + TEST_STRING_2
                    + DELIM + TEST_STRING_3;
            REQUIRE(actual == expected);
        }
    }

    SECTION("Empty vector returns empty string") {
        util::Vector<util::String> test_input;
        util::String actual = util::join(test_input);
        util::String expected = "";
        REQUIRE(actual == expected);
    }
}

TEST_CASE("split")
{
    util::String DELIM = " ";
    SECTION("Simple string") {
        util::String SIMPLE_STRING = "a b c d";
        util::Vector<util::String> actual = util::split(SIMPLE_STRING, DELIM);
        util::Vector<util::String> expected({"a", "b", "c", "d"});
        REQUIRE(actual == expected);
    }

    SECTION("Complex string") {
        util::String COMPLEX_STRING = " a a aaa  a aa    a ";
        util::Vector<util::String> actual = util::split(COMPLEX_STRING, DELIM);
        util::Vector<util::String> expected({
            "", "a", "a", "aaa", "", "a", "aa", "", "", "", "a", ""
        });
        REQUIRE(actual == expected);
    }

    SECTION("No delimiter in string") {
        util::String NO_DELIMITER_STRING = "aaaa";
        util::Vector<util::String> actual = util::split(NO_DELIMITER_STRING, DELIM);
        util::Vector<util::String> expected({NO_DELIMITER_STRING});
        REQUIRE(actual == expected);
    }

    SECTION("Only delimiters in string") {
        util::String ONLY_DELIMITERS_STRING = "     ";
        util::Vector<util::String> actual = util::split(ONLY_DELIMITERS_STRING, DELIM);
        util::Vector<util::String> expected({"", "", "", "", "", ""});
        REQUIRE(actual == expected);
    }

    SECTION("Empty string returns vector with a single, empty string") {
        util::Vector<util::String> actual = util::split("", DELIM);
        util::Vector<util::String> expected({""});
        REQUIRE(actual == expected);
    }
}

TEST_CASE("trim")
{
    SECTION("Non-trimmable string") {
        util::String TO_TRIM = "abc";
        util::String actual = util::trim(TO_TRIM);
        util::String expected = "abc";
        REQUIRE(actual == expected);
    }

    SECTION("Trimmable string") {
        util::String TO_TRIM = "\n\r\ta a a\ta a    ";
        util::String actual = util::trim(TO_TRIM);
        util::String expected = "a a a\ta a";
        REQUIRE(actual == expected);
    }
}

TEST_CASE("casefold")
{
    SECTION("No need to casefold") {
        util::String TO_CASEFOLD = "abcdefgh";
        util::String actual = util::casefold(TO_CASEFOLD);
        REQUIRE(TO_CASEFOLD == actual);
    }

    SECTION("Casefoldable") {
        util::String TO_CASEFOLD = "AbCdEfGh";
        util::String actual = util::casefold(TO_CASEFOLD);
        util::String expected = "abcdefgh";
        REQUIRE(actual == expected);
    }
}

TEST_CASE("hasalnum")
{
    SECTION("Has alphanumeric characters only") {
        util::String ALPHANUMERIC_ONLY = "abcdefABCDEF1234";
        REQUIRE(util::hasalnum(ALPHANUMERIC_ONLY) == true);
    }

    SECTION("Does not have alphanumeric characters") {
        util::String NO_ALPHANUMERIC = "\t\r\n@$*()";
        REQUIRE(util::hasalnum(NO_ALPHANUMERIC) == false);
    }

    SECTION("Has non-alphanumeric characters with alphanumeric characters") {
        util::String MIX = "abcdefABCDEF1234\t\r\n@$*()";
        REQUIRE(util::hasalnum(MIX) == true);
    }
}
