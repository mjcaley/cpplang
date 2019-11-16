#pragma once

#include "Context.hpp"
#include "States/States.hpp"
#include "States/Start.hpp"
#include "Tokens.hpp"


namespace cpplang
{
    template<typename IStream>
    class Lexer
    {
    public:
        explicit Lexer(IStream&& stream) : context(Context(std::move(stream))), state(Start(context)) {}

        using Pos = typename Context<IStream>::StreamPos;

        Token<Pos> emit()
        {
            auto [token, new_state] = state();
            state = new_state;

            return token;
        }

    private:
        Context<IStream> context;
        Mode<Context<IStream>> state;
    };
}
