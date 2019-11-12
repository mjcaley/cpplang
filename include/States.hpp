#pragma once

#include <algorithm>
#include <array>
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

        using CharacterCollection = std::vector<typename ContextCls::StreamChar>;

    protected:
        ContextCls& context;

        static constexpr std::array<typename ContextCls::StreamChar, 3> whitespace { {'\v', '\f', ' '} };

        std::string append_while(const CharacterCollection& characters)
        {
            std::string found;
            while (context.get_current()) {
                auto current = *context.get_current_char();
                auto result = std::find(std::begin(characters), std::end(characters), current);
                if (result != std::end(characters)) {
                    found += current;
                    context.advance();
                } else {
                    break;
                }
            }

            return found;
        }

        std::string append_while_not(const CharacterCollection& characters)
        {
            std::string found;
            while (context.get_current()) {
                auto current = *context.get_current_char();
                auto result = std::find(std::begin(characters), std::end(characters), current);
                if (result == std::end(characters)) {
                    found += current;
                    context.advance();
                } else {
                    break;
                }
            }

            return found;
        }

        void skip_until(const CharacterCollection& characters)
        {
            while (context.get_current()) {
                auto current = *context.get_current_char();
                auto result = std::find(std::begin(characters), std::end(characters), current);
                if (result == std::end(characters)) {
                    context.advance();
                } else {
                    break;
                }
            }
        }

        void skip_while(const CharacterCollection& characters)
        {
            while (context.get_current()) {
                auto current = *context.get_current_char();
                auto result = std::find(std::begin(characters), std::end(characters), current);
                if (result != std::end(characters)) {
                    context.advance();
                } else {
                    break;
                }
            }
        }

        void skip_whitespace()
        {
            while (context.get_current()) {
                auto current = *context.get_current_char();
                auto result = std::find(std::begin(whitespace), std::end(whitespace), current);
                if (result != std::end(whitespace)) {
                    context.advance();
                } else {
                    break;
                }
            }
        }

        bool match(const typename ContextCls::StreamChar character)
        {
            if (context.get_current_char().has_value())
            {
                return *context.get_current_char() == character;
            }
            else
            {
                return false;
            }
        }

        bool match(const CharacterCollection& characters)
        {
            if (context.get_current_char())
            {
                auto result = std::find(std::begin(characters), std::end(characters), *context.get_current_char());
                return result != std::end(characters);
            }
            else
            {
                return false;
            }
        }

        bool match_next(const typename ContextCls::StreamChar character)
        {
            if (context.get_next_char().has_value())
            {
                return *context.get_next_char() == character;
            }
            else
            {
                return false;
            }
        }

        bool match_next(const CharacterCollection& characters)
        {
            if (context.get_next_char())
            {
                auto result = std::find(std::begin(characters), std::end(characters), *context.get_next_char());
                return result != std::end(characters);
            }
            else
            {
                return false;
            }
        }
    };
}
