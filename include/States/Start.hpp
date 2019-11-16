#pragma once

#include <variant>
#include "Position.hpp"
#include "States.hpp"
#include "Tokens.hpp"


namespace cpplang
{
//    template<typename ContextCls>
//    class IsEOF;

    template<typename ContextCls>
    class Start : public Mode<ContextCls>
    {
    public:
        explicit Start(ContextCls& context) : Mode(context) {}

        std::variant<Token<typename ContextCls::StreamPos>, std::unique_ptr<Mode<ContextCls>>> step() override
        {
            context.advance();
            context.advance();
            context.push_indent(0);

            return std::make_unique(IsEOF<ContextCls>(context));
        }
    };
}
