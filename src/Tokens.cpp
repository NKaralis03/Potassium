#include "Tokens.h"

namespace Tokens
{

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
}
