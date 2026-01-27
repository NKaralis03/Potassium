#ifndef PARSER_H
#define PARSER_H

#include "Tokens.h"

#define SUCCESS true
#define FAIL false

// Macro lookup table for terminals
#define TOKEN(x, ...) constexpr bool TERMINAL_##x = true;
#include "TokenTypes.def"
#undef TOKEN

// Macro lookup for non-terminals
#define PROD(x, ...) constexpr bool TERMINAL_##x = false;
#include "Productions.def"
#undef PROD

#define IS_TERMINAL(x) (TERMINAL_##x)

// Match function
/*#define MATCH(token)                                   \
    if (currentToken.type == Tokens::TokenType::token) \
        consume();                                     \
    else                                               \
        return FAIL;
*/

// Expand function, used in recursive descent
#define EXPAND(name)               \
    if constexpr (TERMINAL_##name) \
        MATCH(name);               \
    else                           \
        parse_##name();

// Helper macros for expanding each argument
#define EXPAND_EACH_1(a) EXPAND(a)
#define EXPAND_EACH_2(a, b) \
    EXPAND(a);              \
    EXPAND(b)
#define EXPAND_EACH_3(a, b, c) \
    EXPAND(a);                 \
    EXPAND(b);                 \
    EXPAND(c)
#define EXPAND_EACH_4(a, b, c, d) \
    EXPAND(a);                    \
    EXPAND(b);                    \
    EXPAND(c);                    \
    EXPAND(d)
#define EXPAND_EACH_5(a, b, c, d, e) \
    EXPAND(a);                       \
    EXPAND(b);                       \
    EXPAND(c);                       \
    EXPAND(d);                       \
    EXPAND(e)
#define EXPAND_EACH_6(a, b, c, d, e, f) \
    EXPAND(a);                          \
    EXPAND(b);                          \
    EXPAND(c);                          \
    EXPAND(d);                          \
    EXPAND(e);                          \
    EXPAND(f)
#define EXPAND_EACH_7(a, b, c, d, e, f, g) \
    EXPAND(a);                             \
    EXPAND(b);                             \
    EXPAND(c);                             \
    EXPAND(d);                             \
    EXPAND(e);                             \
    EXPAND(f);                             \
    EXPAND(g)
#define EXPAND_EACH_8(a, b, c, d, e, f, g, h) \
    EXPAND(a);                                \
    EXPAND(b);                                \
    EXPAND(c);                                \
    EXPAND(d);                                \
    EXPAND(e);                                \
    EXPAND(f);                                \
    EXPAND(g);                                \
    EXPAND(h)
#define EXPAND_EACH_9(a, b, c, d, e, f, g, h, i) \
    EXPAND(a);                                   \
    EXPAND(b);                                   \
    EXPAND(c);                                   \
    EXPAND(d);                                   \
    EXPAND(e);                                   \
    EXPAND(f);                                   \
    EXPAND(g);                                   \
    EXPAND(h);                                   \
    EXPAND(i)

#define GET_EXPAND_MACRO(_1, _2, _3, _4, _5, _6, _7, _8, _9, NAME, ...) NAME
#define EXPAND_SEQUENCE(...) \
    GET_EXPAND_MACRO(__VA_ARGS__, EXPAND_EACH_9, EXPAND_EACH_8, EXPAND_EACH_7, EXPAND_EACH_6, EXPAND_EACH_5, EXPAND_EACH_4, EXPAND_EACH_3, EXPAND_EACH_2, EXPAND_EACH_1)(__VA_ARGS__)

class Parser
{
private:
// I want to automatically generate production functions from macros
#define PROD(name, ...)              \
    bool parse_##name()              \
    {                                \
        EXPAND_SEQUENCE(__VA_ARGS__) \
        return SUCCESS;              \
    }

#include "Productions.def"
#undef PROD

public:
    // Recursive descent parser: Should take in a sequence of tokens, and production rules
    static bool Parse();
};

#endif
