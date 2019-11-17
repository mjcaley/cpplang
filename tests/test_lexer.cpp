#include "catch.hpp"
#include <string>
#include <sstream>

#include "Lexer/Lexer.hpp"

TEST_CASE("Lexer constructor", "[lexer]")
{
    std::string input {"abc"};

    SECTION("Lexer is constructed")
    {
        cpplang::Lexer lexer { std::stringstream {input} };
    }
}

TEST_CASE("Emits token", "[lexer]")
{
    std::string input { "123" };

    SECTION("Emits token")
    {
        cpplang::Lexer lexer { std::stringstream {input} };
        //auto result = lexer.emit();
    };
}
