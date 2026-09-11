#include "Parser.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <type_traits>

class AST;

void Parser::CONSUME(ParsingContext &ctx, AST *ast)
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
bool Parser::MATCH(ParsingContext &ctx, AST *ast)
{
    Token currentToken = peek_token(ctx);
    // std::cout << "Matching " << currentToken.str << " with " << static_cast<int>(T::value) << std::endl;

    if (static_cast<int>(currentToken.type) == static_cast<int>(T::value))
    {
        std::cout << "Matched " << currentToken.str << std::endl;

        CONSUME(ctx, ast);
    }
    return (static_cast<int>(currentToken.type) == static_cast<int>(T::value));
}

/* This function is a compile time wrapper for a symbol
   it either resolves to MATCH or Parse based on if the
   symbol is classified as a terminal */
template <typename T>
bool inline Parser::EXPAND(ParsingContext &ctx, AST *ast)
{

    /* This should likely be a call to push the current node onto the AST */
    ASTNode *currNode = new ASTNode(ctx.CurrentToken());
    ast->push(currNode);

    if constexpr (is_terminal<T>::value)
    {
        return MATCH<T>(ctx, ast);
    }
    else
    {
        /* Must move AST cursor when we start a new parse. Since we may backtrack. */
        /* Cursor should initially be a leaf that we will append onto */

        ast->pushCursor(currNode);
        return Parse<T>(ctx, ast);
    }
}

/* This is a wrapper for returning the current token.
   this could likely be inline. */
inline Token Parser::peek_token(ParsingContext &ctx)
{
    return {ctx.CurrentToken()};
}

std::tuple<bool, AST *> Parser::parse(std::vector<Token> &tokens)
{
    ParsingContext ctx(tokens);

    /* Construct AST */
    AST *ast = new AST();

    bool ok = Parse<file>(ctx, ast);

    // Only succeed if the start symbol matched and we've consumed all input
    return {ok && (ctx.position == ctx.tokens.size()), ast};
}