#pragma once

#include <memory>
#include <sstream>
#include <string>
#include "Lexer/Context.hpp"
#include "Lexer/Modes.hpp"

template<typename IStream>
class PublicMode : public cpplang::Mode<IStream>
{
public:
    explicit PublicMode(cpplang::Context<IStream>& context) : cpplang::Mode<IStream>(context) {}

    using CharacterCollection = typename cpplang::Mode<IStream>::CharacterCollection;

    typename cpplang::Mode<IStream>::Union step() override
    {
        return std::make_unique<PublicMode>(this->context);
    }

    const cpplang::Context<IStream>& get_context() { return this->context; }

    std::string public_append_while(const CharacterCollection& characters)
    {
        return cpplang::Mode<IStream>::append_while(characters);
    }

    std::string public_append_while_not(const CharacterCollection& characters)
    {
        return cpplang::Mode<IStream>::append_while_not(characters);
    }

    void public_skip_until(const CharacterCollection& characters)
    {
        cpplang::Mode<IStream>::skip_until(characters);
    }

    void public_skip_while(const CharacterCollection& characters)
    {
        cpplang::Mode<IStream>::skip_while(characters);
    }

    void public_skip_whitespace()
    {
        cpplang::Mode<IStream>::skip_whitespace();
    }

    bool public_match(const typename cpplang::Context<IStream>::Char character)
    {
        return cpplang::Mode<IStream>::match(character);
    }

    bool public_match(const CharacterCollection& characters)
    {
        return cpplang::Mode<IStream>::match(characters);
    }

    bool public_match_next(const typename cpplang::Context<IStream>::Char character)
    {
        return cpplang::Mode<IStream>::match_next(character);
    }

    bool public_match_next(const CharacterCollection& characters)
    {
        return cpplang::Mode<IStream>::match_next(characters);
    }
};

cpplang::Context<std::stringstream> context_at_current(const std::string& input);
