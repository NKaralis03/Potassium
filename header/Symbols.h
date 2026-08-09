#ifndef SYMBOLS_H
#define SYMBOLS_H

namespace Symbols
{
    enum class SymbolEnum
    {
    // define tokens here dynamically through a macro
#define SYMBOL(name, ...) name,
#include "SymbolTypes.def"
#undef SYMBOL

#define TOKEN(name, ...) name,
#include "TokenTypes.def"
#undef TOKEN
    };

    enum class SymbolType
    {
#define SYMBOL(name, ...) name,
#include "SymbolTypes.def"
#undef SYMBOL

#define TOKEN(name, ...) name,
#include "TokenTypes.def"
#undef TOKEN
    };

    template <SymbolEnum S>
    struct Symbol
    {
        static constexpr SymbolEnum value = S;
    };

#define SYMBOL(name, ...) \
    using name = Symbol<SymbolEnum::name>;

#include "SymbolTypes.def"
#undef SYMBOL

#define TOKEN(name, ...) \
    using name = Symbol<SymbolEnum::name>;

#include "TokenTypes.def"
#undef TOKEN

    template <typename S>
    struct is_terminal : std::false_type
    {
    };

//------DEFINES A STRUCT THAT MARKS ALL TOKENS AS TERMINALS-----//
#define TOKEN(name, ...)                      \
    template <>                               \
    struct is_terminal<name> : std::true_type \
    {                                         \
    };
#include "TokenTypes.def"
#undef TOKEN
    //-------------------------------------------------------------//

#define SUCCESS true
#define FAIL false

// Macro lookup table for terminals
#define TOKEN(x, ...) constexpr bool TERMINAL_##x = true;
#include "TokenTypes.def"
#undef TOKEN

// Macro lookup for non-terminals
#define SYMBOL(x, ...) constexpr bool TERMINAL_##x = false;
#include "SymbolTypes.def"
#undef SYMBOL

#define IS_TERMINAL(x) (TERMINAL_##x)

}

#endif