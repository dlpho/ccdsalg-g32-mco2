#ifndef NODE_H
#define NODE_H

#include <stdbool.h>

typedef struct nodeTag
{
    Str20 key;
    bool visited;
    struct nodeTag *leftNode;
    struct nodeTag *rightNode;
} Node;

Node *createNode(Str20 key);
void freeNode(Node *node);

#endif // NODE_H