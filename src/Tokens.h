#ifndef TOKENS_H
#define TOKENS_H

#include <string>
#include <vector>
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

    std::string toString(TokenType type);

    struct Token
    {
        TokenType type;
        std::string str;

        Token(TokenType type_, std::string str_) : type(type_), str(str_) {}
        Token(const Token &token_) : type(token_.type), str(token_.str) {}
        Token() : type(TokenType::AMPERSTAND), str("") {}
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