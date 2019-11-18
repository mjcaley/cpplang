#pragma once

#include <algorithm>
#include <array>
#include <exception>
#include <memory>
#include <string>
#include <utility>
#include <variant>
#include <vector>

#include "Lexer/Context.hpp"
#include "Tokens.hpp"
#include "Context.hpp"


namespace cpplang
{
    template<typename IStream>
    class Mode
    {
    public:
        explicit Mode(Context<IStream>& context) : context(context) {}

        using CharacterCollection = std::vector<typename Context<IStream>::Char>;
        using Pos = typename Context<IStream>::Pos;
        using Tok = cpplang::Token<Pos>;
        using ModePtr = std::unique_ptr<cpplang::Mode<IStream>>;
        using Union = std::variant<Tok, ModePtr>;

        virtual const char* name()
        {
            return "Mode";
        }

        virtual Union step()
        {
            auto token = emit(TokenType::ERROR);

            return token;
        }

    protected:
        Context<IStream>& context;

        Tok emit(TokenType type, Pos position, std::string value)
        {
            return Tok { type, position, value };
        }

        Tok emit(TokenType type, Pos position)
        {
            return emit(type, position, "");
        }

        Tok emit(TokenType type, std::string value)
        {
            auto pos = context.get_current_position().value_or(Pos {});
            return emit(type, pos, value);
        }

        Tok emit(TokenType type)
        {
            return emit(type, "");
        }

        template<typename NextMode>
        ModePtr transition()
        {
            return std::make_unique<NextMode>(context);
        }

        static constexpr std::array<typename Context<IStream>::Char, 3> whitespace { '\v', '\f', ' ' };

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

        bool match(const typename Context<IStream>::Char character)
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

        bool match_next(const typename Context<IStream>::Char character)
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

    // Forward declare modes
    template<typename IStream> class IsEOF;
    template<typename IStream> class Indent;
    template<typename IStream> class Dedent;
    template<typename IStream> class Operators;
    template<typename IStream> class Number;
    template<typename IStream> class String;
    template<typename IStream> class Word;
    template<typename IStream> class End;

    template<typename IStream>
    class Start : public Mode<IStream>
    {
    public:
        explicit Start(Context<IStream>& context) : Mode<IStream>(context) {}

        using type = Start<IStream>;
        using Mode<IStream>::CharacterCollection;
        using Mode<IStream>::Pos;
        using Mode<IStream>::Tok;
        using Mode<IStream>::ModePtr;
        using Mode<IStream>::Union;

        const char* name() override
        {
            return "Start";
        }

        typename Mode<IStream>::Union step() override
        {
            this->context.advance();
            this->context.advance();
            this->context.push_indent(0);

            auto mode = transition<IsEOF<IStream>>();

            return mode;
        }
    };

    template<typename IStream>
    class Indent : public Mode<IStream>
    {
    public:
        explicit Indent(Context<IStream>& context) : Mode<IStream>(context) {}

        using type = Indent<IStream>;
        using Mode<IStream>::CharacterCollection;
        using Mode<IStream>::Pos;
        using Mode<IStream>::Tok;
        using Mode<IStream>::ModePtr;
        using Mode<IStream>::Union;

        const char* name() override
        {
            return "Indent";
        }

        typename Mode<IStream>::Union step() override
        {
            auto mode = transition<Start<IStream>>();

            return mode;
        }
    };

    template<typename IStream>
    class Dedent : Mode<IStream>
    {
    public:
        explicit Dedent(Context<IStream>& context) : Mode<IStream>(context) {}

        using type = Dedent<IStream>;
        using Mode<IStream>::CharacterCollection;
        using Mode<IStream>::Pos;
        using Mode<IStream>::Tok;
        using Mode<IStream>::ModePtr;
        using Mode<IStream>::Union;

        const char* name() override
        {
            return "Dedent";
        }
    };

    template<typename IStream>
    class IsEOF : public Mode<IStream>
    {
    public:
        explicit IsEOF(Context<IStream>& context) : Mode<IStream>(context) {}

        using type = IsEOF<IStream>;
        using Mode<IStream>::CharacterCollection;
        using Mode<IStream>::Pos;
        using Mode<IStream>::Tok;
        using Mode<IStream>::ModePtr;
        using Mode<IStream>::Union;

        const char* name() override
        {
            return "IsEOF";
        }

        typename Mode<IStream>::Union step() override
        {
            auto ret = std::make_unique<Start<IStream>>(this->context);

            return ret;
        }
    };

    template<typename IStream>
    class Operators : public Mode<IStream>
    {
    public:
        explicit Operators(Context<IStream>& context) : Mode<IStream>(context) {}

        using type = Operators<IStream>;
        using Mode<IStream>::CharacterCollection;
        using Mode<IStream>::Pos;
        using Mode<IStream>::Tok;
        using Mode<IStream>::ModePtr;
        using Mode<IStream>::Union;

        const char* name() override
        {
            return "Operators";
        }
    };

    template<typename IStream>
    class Number : public Mode<IStream>
    {
    public:
        explicit Number(Context<IStream>& context) : Mode<IStream>(context) {}

        using type = Number<IStream>;
        using Mode<IStream>::CharacterCollection;
        using Mode<IStream>::Pos;
        using Mode<IStream>::Tok;
        using Mode<IStream>::ModePtr;
        using Mode<IStream>::Union;

        const char* name() override
        {
            return "Number";
        }
    };

    template<typename IStream>
    class String : public Mode<IStream>
    {
    public:
        explicit String(Context<IStream>& context) : Mode<IStream>(context) {}

        using type = String<IStream>;
        using Mode<IStream>::CharacterCollection;
        using Mode<IStream>::Pos;
        using Mode<IStream>::Tok;
        using Mode<IStream>::ModePtr;
        using Mode<IStream>::Union;

        const char* name() override
        {
            return "String";
        }
    };

    template<typename IStream>
    class Word : public Mode<IStream>
    {
    public:
        explicit Word(Context<IStream>& context) : Mode<IStream>(context) {}

        using type = Word<IStream>;
        using Mode<IStream>::CharacterCollection;
        using Mode<IStream>::Pos;
        using Mode<IStream>::Tok;
        using Mode<IStream>::ModePtr;
        using Mode<IStream>::Union;

        const char* name() override
        {
            return "Word";
        }
    };

    template<typename IStream>
    class End : public Mode<IStream>
    {
    public:
        explicit End(Context<IStream>& context) : Mode<IStream>(context) {}

        using type = End<IStream>;
        using Mode<IStream>::CharacterCollection;
        using Mode<IStream>::Pos;
        using Mode<IStream>::Tok;
        using Mode<IStream>::ModePtr;
        using Mode<IStream>::Union;

        const char* name() override
        {
            return "End";
        }
    };
}
