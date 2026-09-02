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
        std::tuple<factor, expressions>
    >;
};

template<>
struct Productions<expressions> {
    using alternatives = std::tuple<
        std::tuple<op, factor, expressions>,
        std::tuple<>
    >;
};

template<>
struct Productions<factor> {
    using alternatives = std::tuple<
        std::tuple<LPAREN, expressions, RPAREN>,
        std::tuple<IDENTIFIER>,
        std::tuple<INTEGERCONST>
    >;
};

template<>
struct Productions<file> {
    using alternatives = std::tuple<
        std::tuple<statements>,
        std::tuple<>
    >;
};

template<>
struct Productions<for_statement> {
    using alternatives = std::tuple<
        std::tuple<FOR, LPAREN, expression, SEMICOLON, variable, RPAREN, LBRACKET, statements, RBRACKET>
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
        std::tuple<LPAREN, expression, RPAREN, QUESTIONMARK, RBRACKET, statements, RBRACKET, COLON, LBRACKET, statements, RBRACKET>
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
struct Productions<parameter> {
    using alternatives = std::tuple<
        std::tuple<INTTYPE>
    >;
};

template<>
struct Productions<parameters> {
    using alternatives = std::tuple<
        std::tuple<parameter, parameters>,
        std::tuple<NEWLINE, parameters>,
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
        std::tuple<function_call>,
        std::tuple<variable>,
        std::tuple<if_statement>,
        std::tuple<loop_statement>
    >;
};

template<>
struct Productions<statements> {
    using alternatives = std::tuple<
        std::tuple<function_decl, statements>,
        std::tuple<statement, statements>,
        std::tuple<NEWLINE, statements>,
        std::tuple<>
    >;
};

template<>
struct Productions<variable> {
    using alternatives = std::tuple<
        std::tuple<IDENTIFIER, ASSIGNMENT, expression, SEMICOLON>,
        std::tuple<INTTYPE, IDENTIFIER, ASSIGNMENT, expression, SEMICOLON>
    >;
};

template<>
struct Productions<while_statement> {
    using alternatives = std::tuple<
        std::tuple<WHILE, LPAREN, expression, RPAREN, LBRACKET, statements, RBRACKET>
    >;
};

#endif