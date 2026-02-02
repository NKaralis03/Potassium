#include <stdio.h>
#include "Lexer.h"
#include "Parser.h"
#include "Tokens.h"

int main(int argc, char **argv)
{
    // Give a file name, and run the lexer on it, and return a file that
    // has tokens listed
    if (argc <= 1)
        return 0;

    std::vector<Tokens::Token> tokens = Lexer::Lexify(argv[1]);
    for (int i = 0; i < tokens.size(); ++i)
    {
        std::cout << Tokens::toString(tokens.at(i).type) << " " << (tokens.at(i).str) << std::endl;
    }

    std::cout << "----- Parsing Stage -----" << std::endl;
    std::cout << "Parsing " << (Parser::parse(tokens) ? "Succeeded" : "Failed") << std::endl;

    return 0;
}