#ifndef AST_H
#define AST_H

#include <vector>
#include "Tokens.h"
#include <stack>
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
    int dataType;

    // children
    std::vector<ASTNode *> children;

    explicit ASTNode(Tokens::Token token_, int dataType_ = 0) : dataType(dataType_)
    {
        nodeType = NODETYPES::OPERAND;
    }
    explicit ASTNode(NODETYPES type_, int dataType_ = 0) : nodeType(type_), dataType(dataType_) {}
};

class AST
{
public:
    // Ability to push children given a context
    void push(ASTNode *child);

    void pushCursor(ASTNode *top);
    void popCursor();
    ASTNode *getCursor();

    // Ability to pop a node and its children as needed

    /* Ability to clean the entire tree
     * Outline: Perform a DFS of the tree, and delete every node
     *           that is encountered on the way UP. That way,
     *           nodes aren't deleted before you access their children
     */
    void clean();
    void clean(ASTNode *node);

private:
    // The root
    ASTNode *root;

    // Current node being looked at
    std::stack<ASTNode *> cursors;

    /* Symbol table to check if variables exist yet */
    SymbolTable symbolTable;

    // Metadata such as how big the tree is
};

#endif