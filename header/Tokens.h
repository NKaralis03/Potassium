#ifndef TOKENS_H
#define TOKENS_H

#include <string>
#include <unordered_map>

namespace Tokens
{
    enum class TokenType
    {
    // define tokens here dynamically through a macro
#define TOKEN(name, lexeme) name,
#include "TokenTypes.def"
#undef TOKEN
    };

    std::string toString(TokenType type)
    {
        switch (type)
        {
#define TOKEN(name, lexeme) \
    case TokenType::name:   \
        return #name;
#include "TokenTypes.def"
#undef TOKEN
        default:
            return "UNKNOWN";
        }
    }

    struct Token
    {
        TokenType type;
        std::string str;

        Token(TokenType type_, std::string str_) : type(type_), str(str_) {}
    };

    struct AvailableTokens
    {
        static inline const std::vector<Token> availableTokens{
#define TOKEN(name, lexeme) Token(TokenType::name, lexeme),
#include "TokenTypes.def"
#undef TOKEN
        };
    };
}

#endif