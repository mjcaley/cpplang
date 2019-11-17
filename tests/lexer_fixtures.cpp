#include "lexer_fixtures.hpp"


cpplang::Context<std::stringstream> context_at_current(const std::string& input)
{
    auto context = cpplang::Context { std::stringstream(input) };
    context.advance();
    context.advance();

    return context;
}
