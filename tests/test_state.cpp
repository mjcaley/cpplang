#include "catch.hpp"
#include <sstream>
#include <vector>
#include "States.hpp"
#include "Context.hpp"


template<typename ContextCls>
class PublicState : public cpplang::State<ContextCls>
{
public:
    explicit PublicState(ContextCls& context) : cpplang::State<ContextCls>(context) {}

    using CharacterCollection = typename cpplang::State<ContextCls>::CharacterCollection;

    const ContextCls& get_context() { return this->context; }

    std::string public_append_while(const CharacterCollection& characters)
    {
        return cpplang::State<ContextCls>::append_while(characters);
    }

    std::string public_append_while_not(const CharacterCollection& characters)
    {
        return cpplang::State<ContextCls>::append_while_not(characters);
    }

    std::string public_skip_until(const CharacterCollection& characters)
    {
        return cpplang::State<ContextCls>::skip_until(characters);
    }
};

auto context_at_current(const std::string& input)
{
    auto context = cpplang::Context { std::stringstream(input) };
    context.advance();
    context.advance();

    return context;
}

TEST_CASE("Base state", "[lexer][states]")
{
    std::string input { "abc" };

    SECTION("append_while single character")
    {
        auto context = context_at_current(input);
        PublicState state { context };
        auto result = state.public_append_while({'a'});

        REQUIRE(result == "a");
        REQUIRE(*state.get_context().get_current_char() == 'b');
    }

    SECTION("append_while multiple characters")
    {
        auto context = context_at_current(input);
        PublicState state { context };
        auto result = state.public_append_while({'a', 'b'});

        REQUIRE(result == "ab");
        REQUIRE(*state.get_context().get_current_char() == 'c');
    }

    SECTION("append_while all characters in input")
    {
        auto context = context_at_current(input);
        PublicState state { context };
        auto result = state.public_append_while({'a', 'b', 'c'});

        REQUIRE(result == "abc");
        REQUIRE(state.get_context().get_current().has_value() == false);
    }

    SECTION("append_while_not single character")
    {
        auto context = context_at_current(input);
        PublicState state { context };
        auto result = state.public_append_while_not({'c'});

        REQUIRE(result == "ab");
        REQUIRE(*state.get_context().get_current_char() == 'c');
    }

    SECTION("append_while_not multiple characters")
    {
        auto context = context_at_current(input);
        PublicState state { context };
        auto result = state.public_append_while_not({'b', 'c'});

        REQUIRE(result == "a");
        REQUIRE(*state.get_context().get_current_char() == 'b');
    }

    SECTION("append_while_not all characters in input")
    {
        auto context = context_at_current(input);
        PublicState state { context };
        auto result = state.public_append_while_not({'a', 'b', 'c'});

        REQUIRE(result.empty());
        REQUIRE(*state.get_context().get_current_char() == 'a');
    }

    SECTION("skip_until one character")
    {
        auto context = context_at_current(input);
        PublicState state { context };
        state.public_append_while_not({'b'});

        REQUIRE(*state.get_context().get_current_char() == 'b');
    }

    SECTION("skip_until multiple characters")
    {
        auto context = context_at_current(input);
        PublicState state { context };
        state.public_append_while_not({'b', 'c'});

        REQUIRE(*state.get_context().get_current_char() == 'b');
    }
}

TEST_CASE("Base state empty string", "[lexer][states]")
{
    std::string input;

    SECTION("append_while empty string", "[lexer][states]")
    {
        auto context = context_at_current(input);
        PublicState state {context};
        auto result = state.public_append_while({'a'});

        REQUIRE(result.empty());
    }
}
