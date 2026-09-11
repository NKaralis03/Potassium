#ifndef PARSER_H
#define PARSER_H

#include "Tokens.h"
#include "Symbols.h"
#include "AST/AST.h"
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
    static void CONSUME(ParsingContext &ctx, AST *ast);

    template <typename T>
    static bool MATCH(ParsingContext &ctx, AST *ast);

    // Expand function for a single symbol (compile-time dispatch via if constexpr)
    template <typename T>
    static bool EXPAND(ParsingContext &ctx, AST *ast);

    // Helper: expand a single alternative (a tuple of symbols)
    template <typename SymbolTuple, size_t... I>
    static bool expand_alternative(std::index_sequence<I...>, ParsingContext &ctx, AST *ast)
    {
        return (EXPAND<std::tuple_element_t<I, SymbolTuple>>(ctx, ast) && ...);
    }

    // Helper: try a specific alternative by index
    template <typename Alternatives, size_t Idx>
    static bool try_alternative(ParsingContext &ctx, AST *ast)
    {
        using alt = std::tuple_element_t<Idx, Alternatives>;
        constexpr size_t num_symbols = std::tuple_size_v<alt>;

        size_t saved_position = ctx.position;

        if (expand_alternative<alt>(
                std::make_index_sequence<num_symbols>{}, ctx, ast))
        {
            return true;
        }

        ctx.position = saved_position;
        return false;
    }

    // Helper: try all alternatives with backtracking
    template <typename Alternatives, size_t... Indices>
    static bool try_all_alternatives(std::index_sequence<Indices...>, ParsingContext &ctx, AST *ast)
    {
        return (try_alternative<Alternatives, Indices>(ctx, ast) || ...);
    }

    // Main parse function for any non-terminal
    template <typename NT>
    static bool Parse(ParsingContext &ctx, AST *ast)
    {
        using alts = typename Productions<NT>::alternatives;
        constexpr size_t num_alts = std::tuple_size_v<alts>;

        bool success = try_all_alternatives<alts>(std::make_index_sequence<num_alts>{}, ctx, ast);

        /* If a parsing operation is unsuccessful, then clean */
        if (!success)
        {
            ast->clean(ast->getCursor());
            ast->popCursor(); // go to previous cursor
        }

        return success;
    }

public:
    static Token peek_token(ParsingContext &ctx);
    // kicks off the template specializations
    static std::tuple<bool, AST *> parse(std::vector<Token> &tokens);
};

#endif
