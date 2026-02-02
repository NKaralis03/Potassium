#ifndef PRODUCTIONS_H
#define PRODUCTIONS_H

#include "Symbols.h"
#include <tuple>

// Productions template specializations
template<typename T>
struct Productions;

using namespace Symbols;

template<>
struct Productions<expression> {
    using alternatives = std::tuple<
        std::tuple<LPAREN, expression, RPAREN>,
        std::tuple<expression, op, expression>,
        std::tuple<factor>
    >;
};

template<>
struct Productions<factor> {
    using alternatives = std::tuple<
        std::tuple<IDENTIFIER>,
        std::tuple<INTEGERCONST>
    >;
};

template<>
struct Productions<file> {
    using alternatives = std::tuple<
        std::tuple<statement>,
        std::tuple<>
    >;
};

template<>
struct Productions<for_statement> {
    using alternatives = std::tuple<
        std::tuple<FOR, LPAREN, expression, SEMICOLON, variable, RPAREN, LBRACKET, statement, RBRACKET>
    >;
};

template<>
struct Productions<function_call> {
    using alternatives = std::tuple<
        std::tuple<IDENTIFIER, LPAREN, parameters, RPAREN, SEMICOLON>
    >;
};

template<>
struct Productions<function_decl> {
    using alternatives = std::tuple<
        std::tuple<returnType, IDENTIFIER, LPAREN, parameters, RPAREN, LBRACKET, statement, RBRACKET>
    >;
};

template<>
struct Productions<if_statement> {
    using alternatives = std::tuple<
        std::tuple<LPAREN, expression, RPAREN, QUESTIONMARK, RBRACKET, statement, RBRACKET, COLON, LBRACKET, statement, RBRACKET>
    >;
};

template<>
struct Productions<loop_statement> {
    using alternatives = std::tuple<
        std::tuple<while_statement>,
        std::tuple<for_statement>
    >;
};

template<>
struct Productions<op> {
    using alternatives = std::tuple<
        std::tuple<AMPERSTAND>,
        std::tuple<STAR>,
        std::tuple<PLUS>,
        std::tuple<MINUS>,
        std::tuple<NOTEQUALITY>,
        std::tuple<EQUALITY>,
        std::tuple<LESSTHAN>,
        std::tuple<GREATERTHAN>,
        std::tuple<GE>,
        std::tuple<LE>
    >;
};

template<>
struct Productions<parameters> {
    using alternatives = std::tuple<
        std::tuple<INTTYPE, parameters>,
        std::tuple<>
    >;
};

template<>
struct Productions<returnType> {
    using alternatives = std::tuple<
        std::tuple<INTTYPE>
    >;
};

template<>
struct Productions<statement> {
    using alternatives = std::tuple<
        std::tuple<function_decl, statement>,
        std::tuple<statementABS, statement>,
        std::tuple<>
    >;
};

template<>
struct Productions<statementABS> {
    using alternatives = std::tuple<
        std::tuple<function_call>,
        std::tuple<variable>,
        std::tuple<if_statement>,
        std::tuple<loop_statement>
    >;
};

template<>
struct Productions<variable> {
    using alternatives = std::tuple<
        std::tuple<IDENTIFIER, ASSIGNMENT, expression, SEMICOLON>
    >;
};

template<>
struct Productions<while_statement> {
    using alternatives = std::tuple<
        std::tuple<WHILE, LPAREN, expression, RPAREN, LBRACKET, statement, RBRACKET>
    >;
};

#endif