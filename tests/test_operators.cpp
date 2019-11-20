#include "catch.hpp"
#include <cstring>
#include <utility>
#include <variant>
#include "lexer_fixtures.hpp"
#include "Lexer/Modes.hpp"
#include "Tokens.hpp"


TEST_CASE("Emit operator tokens", "[lexer][modes][operators]")
{
    using namespace cpplang;
    auto params = GENERATE(
            std::pair { "\n", TokenType::NEWLINE },

            std::pair { ".", TokenType::DOT },
            std::pair { ":", TokenType::COLON },
            std::pair { ",", TokenType::COMMA },

            std::pair { "+", TokenType::PLUS },
            std::pair { "-", TokenType::MINUS },
            std::pair { "*", TokenType::MULTIPLY },
            std::pair { "/", TokenType::DIVIDE },
            std::pair { "**", TokenType::EXPONENT },
            std::pair { "%", TokenType::MODULO },

            std::pair { "=", TokenType::ASSIGN },
            std::pair { "+=", TokenType::PLUS_ASSIGN },
            std::pair { "-=", TokenType::MINUS_ASSIGN },
            std::pair { "*=", TokenType::MULTIPLY_ASSIGN },
            std::pair { "/=", TokenType::DIVIDE_ASSIGN },
            std::pair { "**=", TokenType::EXPONENT_ASSIGN },
            std::pair { "%=", TokenType::MODULO_ASSIGN },

            std::pair { "==", TokenType::EQ },
            std::pair { "!=", TokenType::NE },
            std::pair { "<", TokenType::LT },
            std::pair { ">", TokenType::GT },
            std::pair { "<=", TokenType::LT_EQ },
            std::pair { ">=", TokenType::GT_EQ },

            std::pair { "(", TokenType::LPAREN },
            std::pair { "{", TokenType::LBRACE },
            std::pair { "[", TokenType::LSQUARE }
    );

    SECTION("token")
    {
        auto context = context_at_current(params.first);
        Operators operators {context};
        auto result = operators.step();
        auto token = std::get<cpplang::Token>(result);

        REQUIRE(token.type == params.second);
    }
}

TEST_CASE("Emit right-bracket tokens", "[lexer][modes][operators]")
{
    using namespace cpplang;
    auto params = GENERATE(
        std::pair { "()", TokenType::RPAREN },
        std::pair { "{}", TokenType::RBRACE },
        std::pair { "[]", TokenType::RSQUARE }
    );

    SECTION("token")
    {
        auto context = context_at_current(params.first);
        context.push_bracket(context.get_current()->character);
        context.advance();

        Operators operators {context};
        auto result = operators.step();
        auto token = std::get<cpplang::Token>(result);

        REQUIRE(token.type == params.second);
    }
}
