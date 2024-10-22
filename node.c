#ifndef NODE_C
#define NODE_C

#include "node.h"
#include "def.h"

Node *createNode(Str20 key)
{
    Node *node = (Node *)malloc(sizeof(Node));

    // if allocation of memory fails
    if (node == NULL)
    {
        exit(MALLOC_ERROR);
    }

    // copy given key into vertex
    strcpy(node->key, key);

    // set visited as false by default
    node->visited = false;

    return node;
}

void freeNode(Node *node)
{
    if (node != NULL)
    {
        free(node);
    }
}

#endif // NODE_C