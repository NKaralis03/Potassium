#ifndef PARSER_H
#define PARSER_H

#include "Tokens.h"
#include "Symbols.h"
#include "Productions.h"
#include <iostream>
using namespace Tokens;
using namespace Symbols;

struct ParsingContext
{
    std::vector<Token> tokens;
    size_t position = 0;

    ParsingContext(const std::vector<Token> &tokens_) : tokens(tokens_) {}

    Token CurrentToken()
    {
        if (position < tokens.size())
            return tokens[position];
        // Return a default-constructed Token when out of range (acts like EOF/sentinel)
        return Token();
    }
};

template <auto T>
void print_type()
{
    std::cout << __PRETTY_FUNCTION__ << '\n';
}

class Parser
{
private:
    static void CONSUME(ParsingContext &ctx);

    template <typename T>
    static bool MATCH(ParsingContext &ctx);

    // Expand function for a single symbol (compile-time dispatch via if constexpr)
    template <typename T>
    static inline bool EXPAND(ParsingContext &ctx);

    // Helper: expand a single alternative (a tuple of symbols)
    template <typename SymbolTuple, size_t... I>
    static bool expand_alternative(std::index_sequence<I...>, ParsingContext &ctx)
    {
        return (EXPAND<std::tuple_element_t<I, SymbolTuple>>(ctx) && ...);
    }

    // Helper: try a specific alternative by index
    template <typename Alternatives, size_t Idx>
    static bool try_alternative(ParsingContext &ctx)
    {
        using alt = std::tuple_element_t<Idx, Alternatives>;
        constexpr size_t num_symbols = std::tuple_size_v<alt>;

        size_t saved_position = ctx.position;

        if (expand_alternative<alt>(
                std::make_index_sequence<num_symbols>{}, ctx))
        {
            return true;
        }

        ctx.position = saved_position;
        return false;
    }

    // Helper: try all alternatives with backtracking
    template <typename Alternatives, size_t... Indices>
    static bool try_all_alternatives(std::index_sequence<Indices...>, ParsingContext &ctx)
    {
        return (try_alternative<Alternatives, Indices>(ctx) || ...);
    }

    // Main parse function for any non-terminal
    template <typename NT>
    static bool Parse(ParsingContext &ctx)
    {
        using alts = typename Productions<NT>::alternatives;
        constexpr size_t num_alts = std::tuple_size_v<alts>;
        return try_all_alternatives<alts>(std::make_index_sequence<num_alts>{}, ctx);
    }

public:
    static Token peek_token(ParsingContext &ctx);
    // kicks off the template specializations
    static bool parse(std::vector<Token> &tokens);
};

#endif
