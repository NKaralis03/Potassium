#include "Parser.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <type_traits>

void Parser::CONSUME(ParsingContext &ctx)
{
    assert(("Consume at end of string", ctx.position < ctx.tokens.size()));
    if (ctx.position < ctx.tokens.size())
        ++ctx.position;

    /* Add consumed token to parse tree */
}

/* This function will either consume the current token
   if it is the same, or will error out by returning false
   Decltype is used because symbols are classified as
   subclasses, and this makes sure we compare types. */
template <typename T>
bool Parser::MATCH(ParsingContext &ctx)
{
    Token currentToken = peek_token(ctx);
    // std::cout << "Matching " << currentToken.str << " with " << static_cast<int>(T::value) << std::endl;

    if (static_cast<int>(currentToken.type) == static_cast<int>(T::value))
    {
        std::cout << "Matched " << currentToken.str << std::endl;
        CONSUME(ctx);
    }
    return (static_cast<int>(currentToken.type) == static_cast<int>(T::value));
}

/* This function is a compile time wrapper for a symbol
   it either resolves to MATCH or Parse based on if the
   symbol is classified as a terminal */
template <typename T>
bool inline Parser::EXPAND(ParsingContext &ctx)
{

    if constexpr (is_terminal<T>::value)
        return MATCH<T>(ctx);
    else
        return Parse<T>(ctx);
}

/* This is a wrapper for returning the current token.
   this could likely be inline. */
inline Token Parser::peek_token(ParsingContext &ctx)
{
    return {ctx.CurrentToken()};
}

bool Parser::parse(std::vector<Token> &tokens)
{
    ParsingContext ctx(tokens);
    bool ok = Parse<file>(ctx);
    // Only succeed if the start symbol matched and we've consumed all input
    return ok && (ctx.position == ctx.tokens.size());
}