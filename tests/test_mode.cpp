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
        auto result = state.append_while({'a'});

        REQUIRE(result == "a");
        REQUIRE(*state.context.get_current_char() == 'b');
    }

    SECTION("append_while multiple characters")
    {
        auto context = context_at_current(input);
        PublicMode state { context };
        std::vector<char> match {'a', 'b'};
        auto result = state.append_while(std::begin(match), std::end(match));

        REQUIRE(result == "ab");
        REQUIRE(*state.context.get_current_char() == 'c');
    }

    SECTION("append_while all characters in input")
    {
        auto context = context_at_current(input);
        PublicMode state { context };
        std::vector<char> match {'a', 'b', 'c'};
        auto result = state.append_while(std::begin(match), std::end(match));

        REQUIRE(result == "abc");
        REQUIRE(state.context.get_current().has_value() == false);
    }

    SECTION("append_while_not single character")
    {
        auto context = context_at_current(input);
        PublicMode state { context };
        auto result = state.append_while_not('c');

        REQUIRE(result == "ab");
        REQUIRE(*state.context.get_current_char() == 'c');
    }

    SECTION("append_while_not multiple characters")
    {
        auto context = context_at_current(input);
        PublicMode state { context };
        std::vector<char> match {'b', 'c'};
        auto result = state.append_while_not(std::begin(match), std::end(match));

        REQUIRE(result == "a");
        REQUIRE(*state.context.get_current_char() == 'b');
    }

    SECTION("append_while_not all characters in input")
    {
        auto context = context_at_current(input);
        PublicMode state { context };
        std::vector<char> match {'a', 'b', 'c'};
        auto result = state.append_while_not(std::begin(match), std::end(match));

        REQUIRE(result.empty());
        REQUIRE(*state.context.get_current_char() == 'a');
    }

    SECTION("skip_until one character")
    {
        auto context = context_at_current(input);
        PublicMode state { context };
        state.skip_until('b');

        REQUIRE(*state.context.get_current_char() == 'b');
    }

    SECTION("skip_until multiple characters")
    {
        auto context = context_at_current(input);
        PublicMode state { context };
        std::vector<char> match {'b', 'c'};
        state.skip_until(std::begin(match), std::end(match));

        REQUIRE(*state.context.get_current_char() == 'b');
    }

    SECTION("skip_while one character")
    {
        auto context = context_at_current(input);
        PublicMode state { context };
        state.skip_while('a');

        REQUIRE(*state.context.get_current_char() == 'b');
    }

    SECTION("skip_while multiple characters")
    {
        auto context = context_at_current(input);
        PublicMode state { context };
        std::vector<char> match {'a', 'b'};
        state.skip_while(std::begin(match), std::end(match));

        REQUIRE(*state.context.get_current_char() == 'c');
    }

    SECTION("match doesn't match")
    {
        auto context = context_at_current(input);
        PublicMode state {context};

        REQUIRE_FALSE(state.match('d'));
    }

    SECTION("match matches")
    {
        auto context = context_at_current(input);
        PublicMode state {context};

        REQUIRE(state.match('a'));
    }

    SECTION("match doesn't match collection")
    {
        auto context = context_at_current(input);
        PublicMode state {context};

        std::vector<char> match {'d', 'e'};
        REQUIRE_FALSE(state.match(std::begin(match), std::end(match)));
    }

    SECTION("match matches collection")
    {
        auto context = context_at_current(input);
        PublicMode state {context};

        std::vector<char> match {'a', 'b', 'c'};
        REQUIRE(state.match(std::begin(match), std::end(match)));
    }

    SECTION("match_next doesn't match")
    {
        auto context = context_at_current(input);
        PublicMode state {context};

        REQUIRE_FALSE(state.match_next('d'));
    }

    SECTION("match_next matches")
    {
        auto context = context_at_current(input);
        PublicMode state {context};

        REQUIRE(state.match_next('b'));
    }

    SECTION("match_next doesn't match collection")
    {
        auto context = context_at_current(input);
        PublicMode state {context};

        std::vector<char> match {'d', 'e'};
        REQUIRE_FALSE(state.match_next(std::begin(match), std::end(match)));
    }

    SECTION("match_next matches collection")
    {
        auto context = context_at_current(input);
        PublicMode state {context};

        std::vector<char> match {'a', 'b', 'c'};
        REQUIRE(state.match_next(std::begin(match), std::end(match)));
    }
}

TEST_CASE("Base state empty string", "[lexer][states]")
{
    std::string input;

    SECTION("append_while empty string")
    {
        auto context = context_at_current(input);
        PublicMode state {context};
        auto result = state.append_while('a');

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
        state.skip_whitespace();

        REQUIRE(state.context.get_current_char() == 'a');
    }
}

