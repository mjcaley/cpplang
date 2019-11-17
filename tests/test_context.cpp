#include "catch.hpp"
#include <istream>
#include <string>
#include <sstream>
#include "Lexer/Context.hpp"


TEST_CASE("Input stream", "[context]")
{
    std::string input = "This is some input";

    SECTION("next populated by first character")
    {
        cpplang::Context context { std::istringstream(input, std::istringstream::binary) };
        context.advance();

        REQUIRE(context.get_next());
        REQUIRE(context.get_next()->character == 'T');
    }

    SECTION("next has position of line 1 column 1")
    {
        cpplang::Context context { std::istringstream(input, std::istringstream::binary) };
        context.advance();

        REQUIRE(context.get_next());
        REQUIRE(context.get_next()->position.line() == 1);
        REQUIRE(context.get_next()->position.column() == 1);
    }

    SECTION("current populated by first character")
    {
        cpplang::Context context { std::istringstream(input, std::istringstream::binary) };
        context.advance();
        context.advance();

        REQUIRE(context.get_current());
        REQUIRE(context.get_current()->character == 'T');
    }

    SECTION("current has position of line 1 column 1")
    {
        cpplang::Context context { std::istringstream(input, std::istringstream::binary) };
        context.advance();
        context.advance();

        REQUIRE(context.get_current());
        REQUIRE(context.get_current()->position.line() == 1);
        REQUIRE(context.get_current()->position.column() == 1);
    }
}

TEST_CASE("Can push/pop indents", "[context]")
{
    std::string empty;

    SECTION("Empty pop is false")
    {
        cpplang::Context context { std::istringstream(empty) };
        auto result = context.pop_indent();

        REQUIRE_FALSE(result);
    }

    SECTION("Push indent")
    {
        cpplang::Context context { std::istringstream(empty) };
        context.push_indent(42);

        REQUIRE(context.top_indent() == 42);
    }

    SECTION("Pop indent")
    {
        cpplang::Context context { std::istringstream(empty) };
        context.push_indent(42);
        auto result = context.pop_indent();

        REQUIRE(result == 42);
    }

    SECTION("Top indent")
    {
        cpplang::Context context { std::istringstream(empty) };
        context.push_indent(42);
        auto result = context.top_indent();

        REQUIRE(result == 42);
    }
}

TEST_CASE("Can push/pop brackets", "[context]")
{
    std::string empty;


    SECTION("Empty pop is false")
    {
        cpplang::Context context { std::istringstream(empty) };
        auto result = context.pop_bracket();

        REQUIRE_FALSE(result);
    }

    SECTION("Push bracket")
    {
        cpplang::Context context { std::istringstream(empty) };
        context.push_bracket(42);

        REQUIRE(context.top_bracket() == 42);
    }

    SECTION("Pop bracket")
    {
        cpplang::Context context { std::istringstream(empty) };
        context.push_bracket(42);
        auto result = context.pop_bracket();

        REQUIRE(result == 42);
    }

    SECTION("Top bracket")
    {
        cpplang::Context context { std::istringstream(empty) };
        context.push_bracket(42);
        auto result = context.top_bracket();

        REQUIRE(result == 42);
    }
}
