#ifndef NODE_H
#define NODE_H

typedef struct nodeTag {
    Str20 key;
    struct nodeTag *leftNode;
    struct nodeTag *rightNode;
} Node;

Node *createNode(Str20 key);
void freeNode(Node *node);

#endif