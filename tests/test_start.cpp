#include "catch.hpp"
#include <cstring>
#include <sstream>
#include <variant>
#include "lexer_fixtures.hpp"


std::string empty;

TEST_CASE("Start mode returns string", "[lexer][modes]")
{
    cpplang::Start start { context_at_current(empty) };

    REQUIRE(std::strcmp(start.name(), "Start") == 0);
}

TEST_CASE("Start mode transitions to IsEOF", "[lexer][modes]")
{
    cpplang::Start start { context_at_current(empty) };
    auto result = start.step();
    auto iseof = std::get_if<decltype(start)::ModePtr>(&result);
    REQUIRE(iseof);
    if (iseof)
    {
        REQUIRE(std::strcmp((*iseof)->name(), "IsEOF") == 0);
    }
}
