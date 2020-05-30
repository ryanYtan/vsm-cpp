#include "catch2/catch.hpp"
#include "util/stringutil.h"

using namespace util;

TEST_CASE("join")
{
    std::string TEST_STRING_1 = "aaa";
    std::string TEST_STRING_2 = "bbb ccc";
    std::string TEST_STRING_3 = "dddeee fff";
    std::string DELIM = " / ";

    SECTION("Non-empty vector") {
        SECTION("no delimiter") {
            std::vector<std::string> test_input({
                TEST_STRING_1, TEST_STRING_2, TEST_STRING_3
            });

            std::string actual = join(test_input, "");
            std::string expected = TEST_STRING_1 + TEST_STRING_2 + TEST_STRING_3;
            REQUIRE(actual == expected);
        }
        SECTION("with delimiter") {
            std::vector<std::string> test_input({
                TEST_STRING_1, TEST_STRING_2, TEST_STRING_3
            });

            std::string actual = join(test_input, DELIM);
            std::string expected = TEST_STRING_1
                    + DELIM + TEST_STRING_2
                    + DELIM + TEST_STRING_3;
            REQUIRE(actual == expected);
        }
    }

    SECTION("Empty vector returns empty string") {
        std::vector<std::string> test_input;
        std::string actual = join(test_input);
        std::string expected = "";
        REQUIRE(actual == expected);
    }
}

TEST_CASE("split")
{
    std::string DELIM = " ";

    SECTION("Simple string") {
        std::string SIMPLE_STRING = "a b c d";
        std::vector<std::string> expected({"a", "b", "c", "d"});

        std::vector<std::string> actual;
        split(std::back_inserter(actual), SIMPLE_STRING, DELIM);
        REQUIRE(actual == expected);
    }

    SECTION("Complex string") {
        std::string COMPLEX_STRING = " a a aaa  a aa    a ";
        std::vector<std::string> expected({
            "", "a", "a", "aaa", "", "a", "aa", "", "", "", "a", ""
        });

        std::vector<std::string> actual;
        split(std::back_inserter(actual), COMPLEX_STRING, DELIM);
        REQUIRE(actual == expected);
    }

    SECTION("No delimiter in string") {
        std::string NO_DELIMITER_STRING = "aaaa";
        std::vector<std::string> expected({NO_DELIMITER_STRING});

        std::vector<std::string> actual;
        split(std::back_inserter(actual), NO_DELIMITER_STRING, DELIM);
        REQUIRE(actual == expected);
    }

    SECTION("Only delimiters in string") {
        std::string ONLY_DELIMITERS_STRING = "     ";
        std::vector<std::string> expected({"", "", "", "", "", ""});

        std::vector<std::string> actual;
        split(std::back_inserter(actual), ONLY_DELIMITERS_STRING, DELIM);
        REQUIRE(actual == expected);
    }

    SECTION("Empty string returns vector with a single, empty string") {
        std::vector<std::string> actual;
        split(std::back_inserter(actual), "", DELIM);
        std::vector<std::string> expected({""});
        REQUIRE(actual == expected);
    }
}

TEST_CASE("trim")
{
    SECTION("Non-trimmable string") {
        std::string TO_TRIM = "abc";
        std::string actual = trim(TO_TRIM);
        std::string expected = "abc";
        REQUIRE(actual == expected);
    }

    SECTION("Trimmable string") {
        std::string TO_TRIM = "\n\r\ta a a\ta a    ";
        std::string actual = trim(TO_TRIM);
        std::string expected = "a a a\ta a";
        REQUIRE(actual == expected);
    }
}

TEST_CASE("casefold")
{
    SECTION("No need to casefold") {
        std::string TO_CASEFOLD = "abcdefgh";
        std::string actual = casefold(TO_CASEFOLD);
        REQUIRE(TO_CASEFOLD == actual);
    }

    SECTION("Casefoldable") {
        std::string TO_CASEFOLD = "AbCdEfGh";
        std::string actual = casefold(TO_CASEFOLD);
        std::string expected = "abcdefgh";
        REQUIRE(actual == expected);
    }
}

TEST_CASE("hasalnum")
{
    SECTION("Has alphanumeric characters only") {
        std::string ALPHANUMERIC_ONLY = "abcdefABCDEF1234";
        REQUIRE(hasalnum(ALPHANUMERIC_ONLY) == true);
    }

    SECTION("Does not have alphanumeric characters") {
        std::string NO_ALPHANUMERIC = "\t\r\n@$*()";
        REQUIRE(hasalnum(NO_ALPHANUMERIC) == false);
    }

    SECTION("Has non-alphanumeric characters with alphanumeric characters") {
        std::string MIX = "abcdefABCDEF1234\t\r\n@$*()";
        REQUIRE(hasalnum(MIX) == true);
    }
}
