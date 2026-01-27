#ifndef LEXER_HPP
#define LEXER_HPP

#include <fstream>
#include <stdio.h>
#include <iostream>
#include <unordered_map>
#include <sstream>
#include <regex>
#include "Tokens.h"

using namespace Tokens;

class Lexer
{
private:
    static inline bool isLiteralToken(const std::string &s)
    {
        // One character → always literal
        return (s.size() == 1);
    }

    static std::string regexEscape(const std::string &s)
    {
        static const std::regex special(R"([.^$|()\\[*+?{}])");
        return std::regex_replace(s, special, R"(\$&)");
    }

public:
    // given a fstream, loop through and find
    static std::vector<Token> Lexify(const std::string &filename)
    {
        std::fstream file(filename);
        if (!file.is_open())
            std::cout << "ERROR: File " << filename << " was not opened";

        std::stringstream filestream;
        filestream << file.rdbuf();

        const std::string contents = filestream.str();
        size_t offset = 0;

        std::vector<Token> result;

        while (offset < contents.size())
        {
            bool matched = false;
            std::smatch ws;
            std::regex whitespace(R"(^\s+)");
            if (std::regex_search(contents.begin() + offset, contents.end(), ws, whitespace))
            {
                offset += ws.size();
            }

            for (auto &token : AvailableTokens::availableTokens)
            {

                std::smatch match;
                std::string lexeme = isLiteralToken(token.str) ? regexEscape(token.str) : token.str;
                const std::regex re("^(" + lexeme + ")");

                if (std::regex_search(contents.begin() + offset, contents.end(), match, re))
                {
                    result.push_back(Token(token.type, match[0]));
                    offset += match.length();
                    matched = true;
                    break;
                }
            }

            if (!matched)
            {
                std::cout << "Unexpected symbol: " << std::string(1, contents[offset]) << std::endl;
                return result;
            }
        }

        return result;
    }
};

#endif