#include "catch.hpp"
#include <sstream>
#include <vector>
#include "lexer_fixtures.hpp"


TEST_CASE("Base state", "[lexer][states]")
{
    std::string input { "abc" };

    SECTION("append_while single character")
    {
        auto context = context_at_current(input);
        PublicMode state { context };
        auto result = state.public_append_while({'a'});

        REQUIRE(result == "a");
        REQUIRE(*state.get_context().get_current_char() == 'b');
    }

    SECTION("append_while multiple characters")
    {
        auto context = context_at_current(input);
        PublicMode state { context };
        auto result = state.public_append_while({'a', 'b'});

        REQUIRE(result == "ab");
        REQUIRE(*state.get_context().get_current_char() == 'c');
    }

    SECTION("append_while all characters in input")
    {
        auto context = context_at_current(input);
        PublicMode state { context };
        auto result = state.public_append_while({'a', 'b', 'c'});

        REQUIRE(result == "abc");
        REQUIRE(state.get_context().get_current().has_value() == false);
    }

    SECTION("append_while_not single character")
    {
        auto context = context_at_current(input);
        PublicMode state { context };
        auto result = state.public_append_while_not({'c'});

        REQUIRE(result == "ab");
        REQUIRE(*state.get_context().get_current_char() == 'c');
    }

    SECTION("append_while_not multiple characters")
    {
        auto context = context_at_current(input);
        PublicMode state { context };
        auto result = state.public_append_while_not({'b', 'c'});

        REQUIRE(result == "a");
        REQUIRE(*state.get_context().get_current_char() == 'b');
    }

    SECTION("append_while_not all characters in input")
    {
        auto context = context_at_current(input);
        PublicMode state { context };
        auto result = state.public_append_while_not({'a', 'b', 'c'});

        REQUIRE(result.empty());
        REQUIRE(*state.get_context().get_current_char() == 'a');
    }

    SECTION("skip_until one character")
    {
        auto context = context_at_current(input);
        PublicMode state { context };
        state.public_skip_until({'b'});

        REQUIRE(*state.get_context().get_current_char() == 'b');
    }

    SECTION("skip_until multiple characters")
    {
        auto context = context_at_current(input);
        PublicMode state { context };
        state.public_skip_until({'b', 'c'});

        REQUIRE(*state.get_context().get_current_char() == 'b');
    }

    SECTION("skip_while one character")
    {
        auto context = context_at_current(input);
        PublicMode state { context };
        state.public_skip_while({'a'});

        REQUIRE(*state.get_context().get_current_char() == 'b');
    }

    SECTION("skip_while multiple characters")
    {
        auto context = context_at_current(input);
        PublicMode state { context };
        state.public_skip_while({'a', 'b'});

        REQUIRE(*state.get_context().get_current_char() == 'c');
    }

    SECTION("match doesn't match")
    {
        auto context = context_at_current(input);
        PublicMode state {context};

        REQUIRE_FALSE(state.public_match('d'));
    }

    SECTION("match matches")
    {
        auto context = context_at_current(input);
        PublicMode state {context};

        REQUIRE(state.public_match('a'));
    }

    SECTION("match doesn't match collection")
    {
        auto context = context_at_current(input);
        PublicMode state {context};

        REQUIRE_FALSE(state.public_match({'d', 'e'}));
    }

    SECTION("match matches collection")
    {
        auto context = context_at_current(input);
        PublicMode state {context};

        REQUIRE(state.public_match({'a', 'b', 'c'}));
    }

    SECTION("match_next doesn't match")
    {
        auto context = context_at_current(input);
        PublicMode state {context};

        REQUIRE_FALSE(state.public_match_next('d'));
    }

    SECTION("match_next matches")
    {
        auto context = context_at_current(input);
        PublicMode state {context};

        REQUIRE(state.public_match_next('b'));
    }

    SECTION("match_next doesn't match collection")
    {
        auto context = context_at_current(input);
        PublicMode state {context};

        REQUIRE_FALSE(state.public_match_next({'d', 'e'}));
    }

    SECTION("match_next matches collection")
    {
        auto context = context_at_current(input);
        PublicMode state {context};

        REQUIRE(state.public_match_next({'a', 'b', 'c'}));
    }
}

TEST_CASE("Base state empty string", "[lexer][states]")
{
    std::string input;

    SECTION("append_while empty string")
    {
        auto context = context_at_current(input);
        PublicMode state {context};
        auto result = state.public_append_while({'a'});

        REQUIRE(result.empty());
    }
}

TEST_CASE("Base state whitespace", "[lexer][state]")
{
    std::string input { " \v\fabc" };

    SECTION("skip whitespace")
    {
        auto context = context_at_current(input);
        PublicMode state {context};
        state.public_skip_whitespace();

        REQUIRE(state.get_context().get_current_char() == 'a');
    }
}

