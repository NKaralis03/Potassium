#include "Parser.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <type_traits>

static void CONSUME(ParsingContext &ctx)
{
    assert(("Consume at end of string", ctx.position < ctx.tokens.size()));
    ctx.position += (ctx.position < ctx.tokens.size());
}

template <typename T>
void Parser::MATCH(ParsingContext &ctx)
{
    Token currentToken = peek_token(ctx);

    if (std::is_same_v<T, decltype(currentToken.type)>)
        CONSUME(ctx);
    return (std::is_same_v<T, decltype(currentToken.type)>);
}

template <typename T>
bool inline Parser::EXPAND(ParsingContext &ctx)
{
    if (constexpr(is_terminal<T>::value))
        return MATCH<T>(ctx);
    else
        return Parse<T>(ctx);
}

Token Parser::peek_token(ParsingContext &ctx)
{
    std::cout << "Not implemented: peek_token()" << std::endl;
    return Token{};
}

bool Parser::parse(std::vector<Token> &tokens)
{
    ParsingContext ctx(tokens);
    return Parse<file>(ctx);
}