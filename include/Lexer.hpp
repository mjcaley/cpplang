#pragma once

#include <memory>
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
        explicit Lexer(IStream&& stream) : context(Context(std::move(stream))), state(std::make_unique<Start<Context<IStream>>>(context)) {}

        using Pos = typename Context<IStream>::StreamPos;

        //Token<Pos> emit()
        //{
        //    auto [token, new_state] = state();
        //    state = new_state;

        //    return token;
        //}

    private:
        Context<IStream> context;
	std::unique_ptr<Mode<Context<IStream>>> state;
    };
}
