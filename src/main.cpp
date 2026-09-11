#include <stdio.h>
#include "Lexer/Lexer.h"
#include "Parser/Parser.h"
#include "Tokens.h"

int main(int argc, char **argv)
{
    // Give a file name, and run the lexer on it, and return a file that
    // has tokens listed
    if (argc <= 1)
        return 0;

    std::vector<Tokens::Token> tokens = Lexer::Lexify(argv[1]);
    for (Tokens::Token token : tokens)
    {
        std::cout << Tokens::toString(token.type) << " " << (token.str) << std::endl;
    }

    std::cout << "----- Parsing Stage -----" << std::endl;

    auto [succeeded, _] = Parser::parse(tokens);
    std::cout << "Parsing " << (succeeded ? "Succeeded" : "Failed") << std::endl;

    return 0;
}