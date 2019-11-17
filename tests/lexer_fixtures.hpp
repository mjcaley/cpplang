#pragma once

#include <memory>
#include <sstream>
#include <string>
#include "Lexer/Context.hpp"
#include "Lexer/Modes.hpp"

template<typename ContextCls>
class PublicMode : public cpplang::Mode<ContextCls>
{
public:
    explicit PublicMode(ContextCls& context) : cpplang::Mode<ContextCls>(context) {}

    using CharacterCollection = typename cpplang::Mode<ContextCls>::CharacterCollection;

    typename cpplang::Mode<ContextCls>::Union step() override
    {
        return std::make_unique<PublicMode>(this->context);
    }

    const ContextCls& get_context() { return this->context; }

    std::string public_append_while(const CharacterCollection& characters)
    {
        return cpplang::Mode<ContextCls>::append_while(characters);
    }

    std::string public_append_while_not(const CharacterCollection& characters)
    {
        return cpplang::Mode<ContextCls>::append_while_not(characters);
    }

    void public_skip_until(const CharacterCollection& characters)
    {
        cpplang::Mode<ContextCls>::skip_until(characters);
    }

    void public_skip_while(const CharacterCollection& characters)
    {
        cpplang::Mode<ContextCls>::skip_while(characters);
    }

    void public_skip_whitespace()
    {
        cpplang::Mode<ContextCls>::skip_whitespace();
    }

    bool public_match(const typename ContextCls::Char character)
    {
        return cpplang::Mode<ContextCls>::match(character);
    }

    bool public_match(const CharacterCollection& characters)
    {
        return cpplang::Mode<ContextCls>::match(characters);
    }

    bool public_match_next(const typename ContextCls::Char character)
    {
        return cpplang::Mode<ContextCls>::match_next(character);
    }

    bool public_match_next(const CharacterCollection& characters)
    {
        return cpplang::Mode<ContextCls>::match_next(characters);
    }
};

cpplang::Context<std::stringstream> context_at_current(const std::string& input);
