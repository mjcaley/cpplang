#pragma once

#include <memory>
#include <variant>
#include "Position.hpp"
#include "States.hpp"
#include "Tokens.hpp"


namespace cpplang
{
    template<typename ContextCls>
    class IsEOF;

    template<typename ContextCls>
    class Start : public Mode<ContextCls>
    {
    public:
        explicit Start(ContextCls& context) : Mode<ContextCls>(context) {}

        std::variant<Token<typename ContextCls::StreamPos>, std::unique_ptr<Mode<ContextCls>>> step() override
        {
            this->context.advance();
            this->context.advance();
            this->context.push_indent(0);

            std::variant<Token<typename ContextCls::StreamPos>, std::unique_ptr<Mode<ContextCls>>> ret = std::make_unique<Start<ContextCls>>(this->context);

            return ret;
	}
    };
}
