#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include "Tokens.hpp"


namespace cpplang
{
    template<typename ContextCls>
    class State
    {
    public:
        explicit State(ContextCls& context) : context(context) {}

    protected:
        ContextCls& context;

        using CharacterCollection = std::vector<typename ContextCls::StreamChar>;

        std::string append_while(const CharacterCollection& characters)
        {
            std::string found;
            while (context.get_current()) {
                auto current = *context.get_current_char();
                auto result = std::find(std::begin(characters), std::end(characters), current);
                if (result != std::end(characters)) {
                    found += *result;
                    context.advance();
                } else {
                    break;
                }
            }

            return found;
        }
    };
}
