#ifndef TRAVERSAL_H
#define TRAVERSAL_H

#include "def.h"
#include "graph.h"
#include "queue.h"

/* As per specification, only BFS is required for drawing */
// void traversalsToFile(Graph *graph, Str20 startKey, Graph *treeBfs, Graph *treeDfs);
void traversalsToFile(Graph *graph, Str20 startKey, Graph *treeBfs);
void bfs(FILE *fp, Graph *graph, Str20 startKey, Graph *tree);
void bfsRecursive(FILE *fp, Graph *graph, Str20 key, struct Queue *q, Graph *tree);
/* As per specification, only BFS is required for drawing */
// void dfs(FILE *fp, Graph *graph, Str20 startKey, Graph *tree);
// void dfsRecursive(FILE *fp, Graph *graph, int startIndex, Graph *tree);
void dfs(FILE *fp, Graph *graph, Str20 startKey);
void dfsRecursive(FILE *fp, Graph *graph, int startIndex);
void sortAlphabetically(Graph *graph, int *adjIndices, int count);

#endif // TRAVERSAL_H