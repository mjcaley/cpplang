#pragma once

#include <fstream>
#include <optional>
#include <stack>
#include <string>

#include "Position.hpp"


namespace cpplang
{
    template<typename Char, typename Pos>
    struct Character
    {
        Character() : character('\0'), position({ 1, 1 }) {};
        Character(const Char character, const Pos position) : character(character), position(position) {};

        Char character;
        Pos position;
    };

    template<typename IStream>
    class Context
    {
    public:
        using StreamChar = typename IStream::char_type;
        using StreamPos = typename IStream::int_type;
        using PositionCls = typename cpplang::Position<StreamPos>;
        using CharacterCls = typename cpplang::Character<StreamChar, PositionCls>;

        explicit Context(IStream&& input) : stream(std::move(input)) {};
        ~Context() = default;

        [[nodiscard]] std::optional<CharacterCls> get_current() const
        {
            return current;
        }

        std::optional<StreamChar> get_current_char() const
        {
            if (current)
            {
                return current->character;
            }
            else
            {
                return {};
            }
        }

        std::optional<PositionCls> get_current_position() const
        {
            if (current)
            {
                return current->position;
            }
            else
            {
                return {};
            }
        }

        [[nodiscard]] std::optional<CharacterCls> get_next() const
        {
            return next;
        }

        void push_indent(char indent)
        {
            indents.push(indent);
        }

        std::optional<StreamChar> get_next_char() const
        {
            if (next)
            {
                return next->character;
            }
            else
            {
                return {};
            }
        }

        std::optional<PositionCls> get_next_position() const
        {
            if (next)
            {
                return next->position;
            }
            else
            {
                return {};
            }
        }

        std::optional<char> pop_indent()
        {
            std::optional<char> indent;
            if (!indents.empty())
            {
                indent = indents.top();
                indents.pop();
            }

            return indent;
        }

        [[nodiscard]] std::optional<char> top_indent() const
        {
            std::optional<char> indent;
            if (!indents.empty())
            {
                indent = indents.top();
            }

            return indent;
        }

        void push_bracket(char bracket)
        {
            brackets.push(bracket);
        }

        std::optional<char> pop_bracket()
        {
            std::optional<char> bracket;
            if (!brackets.empty())
            {
                bracket = brackets.top();
                brackets.pop();
            }

            return bracket;
        }

        [[nodiscard]] std::optional<char> top_bracket() const
        {
            std::optional<char> bracket;
            if (!brackets.empty())
            {
                bracket = brackets.top();
            }

            return bracket;
        }

        [[nodiscard]] bool eof() const
        {
            return stream.eof();
        }

        std::optional<CharacterCls> advance()
        {
            current = next;
            StreamChar next_character;
            stream.get(next_character);

            if (stream.eof())
            {
                next.reset();
            }
            else
            {
                // Handle newlines
                if (next_character == '\r')
                {
                    if (stream.peek() == '\n')
                    {
                        stream.get(next_character);
                    }
                    else
                    {
                        next_character = '\n';
                    }
                }

                if (current)
                {
                    if (current->character == '\n')
                    {
                        next = { next_character, {next->position.line() + 1, 1} };
                    }
                    else
                    {
                        next = { next_character, { next->position.line(), next->position.column() + 1 } };
                    }
                }
                else
                {
                    next = { next_character, { 1, 1 }};
                }
            }

            return current;
        }

    private:
        IStream stream;

        std::stack<StreamChar> indents;
        std::stack<StreamChar> brackets;

        std::optional<CharacterCls> current;
        std::optional<CharacterCls> next;
    };
}
