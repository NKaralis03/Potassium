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

void AST::push(ASTNode *child) { cursor->children.push_back(child); }

void AST::clean()
{
    /* Lambda to define the cleaning operation */
    auto cleanLamda = [](ASTNode *node)
    {
        delete node;
    };

    /* Clean action over a DFS */
    /* Begin at root */
    DFS(cleanLamda, root);
    root = nullptr;
}
