#ifndef GRAPH_H
#define GRAPH_H

typedef struct graphTag {
    int numVertices;
    Node **vertices;
    bool **edges;
} Graph;

Graph *createGraph(int num);
Graph *createGraphFromFile(FILE *fp);
void freeGraph(Graph * graph);
void addVertex(Graph *graph, Str20 key);
int vertexDegree(Graph *graph, Node *vertex);
int vertexIndex(Graph *graph, Str20 key);
void addEdge(Graph *graph, Str20 fromKey, Str20 toKey);
void printEdges(Graph* graph);
bool sameKeys(const char *key1, const char *key2);
void strLower(const char *string, char *lower);

#endif