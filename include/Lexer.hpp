#pragma once

#include "Context.hpp"
#include "States.hpp"


namespace cpplang
{
    template<typename IStream>
    class Lexer
    {
    public:
        explicit Lexer(IStream stream) : context(Contet(stream)) {}

    private:
        Context<IStream> context;

    };


}
