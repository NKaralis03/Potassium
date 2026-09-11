#include "AST.h"
#include <type_traits>
#include <functional>

void DFS(std::function<void(ASTNode *)> action, ASTNode *node)
{
    for (ASTNode *child : node->children)
    {
        DFS(action, child);
    }
    action(node);
}

void AST::push(ASTNode *child) { cursors.top()->children.push_back(child); }

void AST::pushCursor(ASTNode *top) { cursors.push(top); }

void AST::popCursor() { cursors.pop(); }

ASTNode *AST::getCursor() { return cursors.top(); }

void AST::clean(ASTNode *node)
{
    if (!node)
        node = root;

    /* Lambda to define the cleaning operation */
    auto cleanLamda = [](ASTNode *node)
    {
        delete node;
    };

    /* Clean action over a DFS */
    /* Begin at root */
    DFS(cleanLamda, node);
}

void AST::clean() { clean(root); }
