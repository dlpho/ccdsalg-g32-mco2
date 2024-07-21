#include"node.h"

Node *createNode(Str20 key) {
    Node * node = (Node *)malloc(sizeof(Node));

    // copy key or vertex ID
    strcpy(node->key, key);

    // set let and right nodes to null
    node->leftNode = NULL;
    node->rightNode = NULL;
    
    return node;
}

void freeNode(Node *node) {
    if (node != NULL) {
        freeNode(node->leftNode);
        freeNode(node->rightNode);
        free(node);
    }
    
}