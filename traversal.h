#ifndef TRAVERSAL_H
#define TRAVERSAL_H

#include "def.h"
#include "graph.h"

void traversalsToFile(Graph* graph, Str20 startKey);
void bfs(FILE *fp, Graph *graph, Str20 startKey);
void bfsRecursive(FILE *fp, Graph *graph, int startIndex);
void dfs(FILE *fp, Graph *graph, Str20 startKey);
void dfsRecursive(FILE *fp, Graph *graph, int startIndex);
void sortAlphabetically(Graph *graph, int *adjIndices, int count);
#endif