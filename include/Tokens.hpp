#pragma once

#include <string>


namespace cpplang
{
    enum class TokenType
    {
        INDENT,
        DEDENT,

        NEWLINE,

        INTEGER,
        FLOAT,
        STRING,
        IDENTIFIER,

        // Keywords
        FUNC,
        STRUCT,
        IF,
        ELIF,
        ELSE,
        WHILE,
        FOR,
        AND,
        NOT,
        OR,
        TRUE,
        FALSE,
        RETURN,

        // Operators
        DOT,
        COLON,
        COMMA,

        // Arithmetic
        PLUS,
        MINUS,
        MULTIPLY,
        DIVIDE,
        MODULO,
        EXPONENT,

        // Assignment
        ASSIGN,
        PLUS_ASSIGN,
        MINUS_ASSIGN,
        MULTIPLY_ASSIGN,
        DIVIDE_ASSIGN,
        MODULO_ASSIGN,
        EXPONENT_ASSIGN,

        // Comparison
        EQ,
        NE,
        LT,
        GT,
        LT_EQ,
        GT_EQ,

        // Brackets
        LPAREN,
        RPAREN,
        LSQUARE,
        RSQUARE,
        LBRACE,
        RBRACE,

        ERROR
    };

    template<typename PositionCls>
    class Token
    {
    public:
        Token(TokenType type, PositionCls position, std::string value) : type(type), position(position), value(value) {}
        Token(TokenType type, PositionCls position) : type(type), position(position), value({}) {}

        TokenType type;
        PositionCls position;
        std::string value;
    };
}
