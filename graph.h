#ifndef GRAPH_H
#define GRAPH_H

#define GRAPH_MALLOC_ERROR 9;
#define VERTICES_MALLOC_ERROR 10;
#define EDGES_MALLOC_ERROR 11;

// graph 
typedef struct graphTag {
    int numVertices;
    Node **vertices;
    bool **edges;
} Graph;

Graph *createGraph(int num);
Graph *createGraphFromFile(FILE *fp);
void addVertex(Graph *graph, Str20 key);
void addEdge(Graph *graph, Str20 fromKey, Str20 toKey);
void freeGraph(Graph * graph);
void printGraph(Graph *graph);
int vertexDegree(Graph *graph, Node *vertex);
int vertexIndex(Graph *graph, Str20 key);
bool sameKeys(const char *key1, const char *key2);
void strLower(const char *string, char *lower);

#endif