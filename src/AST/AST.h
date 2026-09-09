#ifndef AST_H
#define AST_H

#include <vector>
#include "SymbolTable/SymbolTable.h"

enum class NODETYPES
{
    OPERAND,
    SYMBOL,
    LITERAL
};

struct ASTNode
{
    // node type
    NODETYPES nodeType;

    // data type (int, string, etc)
    std::vector<ASTNode *> children;
};

class AST
{
public:
    // Ability to push children given a context
    void push(ASTNode *child);

    // Ability to pop a node and its children as needed

    /* Ability to clean the entire tree
     * Outline: Perform a DFS of the tree, and delete every node
     *           that is encountered on the way UP. That way,
     *           nodes aren't deleted before you access their children
     */
    void clean();

private:
    // The root
    ASTNode *root;

    // Current node being looked at
    ASTNode *cursor;

    /* Symbol table to check if variables exist yet */
    SymbolTable symbolTable;

    // Metadata such as how big the tree is
};

#endif