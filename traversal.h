#ifndef TRAVERSAL_H
#define TRAVERSAL_H

#include "def.h"
#include "graph.h"
#include "queue.h"

void traversalsToFile(Graph *graph, Str20 startKey, Graph *treeBfs, Graph *treeDfs);
void bfs(FILE *fp, Graph *graph, Str20 startKey, Graph *tree); // as per specification, BFS is only required for drawing
void bfsRecursive(FILE *fp, Graph *graph, Str20 key, struct Queue *q, Graph *tree);
void dfs(FILE *fp, Graph *graph, Str20 startKey, Graph *tree);
void dfsRecursive(FILE *fp, Graph *graph, int startIndex, Graph *tree);
void sortAlphabetically(Graph *graph, int *adjIndices, int count);

#endif // TRAVERSAL_H