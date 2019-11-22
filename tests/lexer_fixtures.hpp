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

    using cpplang::Mode<IStream>::step;
    using cpplang::Mode<IStream>::context;

    using cpplang::Mode<IStream>::append_while;
    using cpplang::Mode<IStream>::append_while_not;
    using cpplang::Mode<IStream>::skip_until;
    using cpplang::Mode<IStream>::skip_while;
    using cpplang::Mode<IStream>::skip_whitespace;
    using cpplang::Mode<IStream>::match;
    using cpplang::Mode<IStream>::match_next;
};

cpplang::Context<std::stringstream> context_at_current(const std::string& input);
