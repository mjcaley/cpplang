#pragma once

#include <algorithm>
#include <array>
#include <exception>
#include <memory>
#include <string>
#include <utility>
#include <variant>
#include <vector>

#include "Tokens.hpp"


namespace cpplang
{
    template<typename ContextCls>
    class Mode
    {
    public:
        explicit Mode(ContextCls& context) : context(context) {}

        using CharacterCollection = std::vector<typename ContextCls::StreamChar>;
        using Tok = cpplang::Token<typename ContextCls::PositionCls>;

        virtual std::variant<Tok, std::unique_ptr<Mode>> step()
        {
            auto pos = context.get_current_position().value_or(ContextCls::PositionCls {});
            Tok token { TokenType::ERROR, pos };

            return token;
        }

    protected:
        ContextCls& context;

        static constexpr std::array<typename ContextCls::StreamChar, 3> whitespace { '\v', '\f', ' ' };

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

    template<typename ContextCls>
    class Indent : public Mode<ContextCls>
    {
    public:
        explicit Indent(ContextCls& context) : Mode<ContextCls>(context) {}

        using Tok = cpplang::Token<typename ContextCls::StreamPos>;
        using ModePtr = std::unique_ptr<Mode<ContextCls>>;

        std::variant<Tok, ModePtr> step() override
        {
            std::variant<Tok, ModePtr> ret = std::make_unique<Start<ContextCls>>(this->context);

            return ret;
        }
    };

    template<typename ContextCls>
    class IsEOF;

    template<typename ContextCls>
    class Start : public Mode<ContextCls>
    {
    public:
        explicit Start(ContextCls& context) : Mode<ContextCls>(context) {}

        using Tok = cpplang::Token<typename ContextCls::PositionCls>;
        using ModePtr = std::unique_ptr<Mode<ContextCls>>;

        std::variant<Tok, ModePtr> step() override
        {
            this->context.advance();
            this->context.advance();
            this->context.push_indent(0);

            std::variant<Tok, ModePtr> ret = std::make_unique<IsEOF<ContextCls>>(this->context);

            return ret;
        }
    };

    template<typename ContextCls>
    class Dedent : Mode<ContextCls>
    {
    public:
        explicit Dedent(ContextCls& context) : Mode<ContextCls>(context) {}
    };

    template<typename ContextCls>
    class IsEOF : public Mode<ContextCls>
    {
    public:
        explicit IsEOF(ContextCls& context) : Mode<ContextCls>(context) {}

        using Tok = cpplang::Token<typename ContextCls::PositionCls>;
        using ModePtr = std::unique_ptr<Mode<ContextCls>>;

        std::variant<Tok, ModePtr> step() override
        {
            std::variant<Tok, ModePtr> ret = std::make_unique<Start<ContextCls>>(this->context);

            return ret;
        }
    };

    template<typename ContextCls>
    class Operators : public Mode<ContextCls>
    {
    public:
        explicit Operators(ContextCls& context) : Mode<ContextCls>(context) {}
    };

    template<typename ContextCls>
    class Number : public Mode<ContextCls>
    {
    public:
        explicit Number(ContextCls& context) : Mode<ContextCls>(context) {}
    };

    template<typename ContextCls>
    class String : public Mode<ContextCls>
    {
    public:
        explicit String(ContextCls& context) : Mode<ContextCls>(context) {}
    };

    template<typename ContextCls>
    class Word : public Mode<ContextCls>
    {
    public:
        explicit Word(ContextCls& context) : Mode<ContextCls>(context) {}
    };

    template<typename ContextCls>
    class End : public Mode<ContextCls>
    {
    public:
        explicit End(ContextCls& context) : Mode<ContextCls>(context) {}
    };
}
