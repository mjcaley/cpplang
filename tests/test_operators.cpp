#include "catch.hpp"
#include <cstring>
#include <sstream>
#include <variant>
#include "lexer_fixtures.hpp"
#include "Lexer/Modes.hpp"
#include "Tokens.hpp"



TEST_CASE("Plus token", "[lexer][modes][operators]")
{
    auto context = context_at_current("+");
    cpplang::Operators operators { context };
    auto result = operators.step();
    auto token = std::get<cpplang::Token>(result);

    REQUIRE(token.type == cpplang::TokenType::PLUS);
}
