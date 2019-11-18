#pragma once

#include <memory>
#include "Context.hpp"
#include "Modes.hpp"
#include "Tokens.hpp"


namespace cpplang
{
    template<typename IStream>
    class Lexer
    {
    public:
        explicit Lexer(IStream&& stream) : context(Context(std::move(stream))), state(std::make_unique<Start<IStream>>(context)) {}

    private:
        Context<IStream> context;
    	std::unique_ptr<Mode<IStream>> state;
    };
}
