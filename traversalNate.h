#ifndef TRAVERSAL_H
#define TRAVERSAL_H

#include "def.h"
#include "graph.h"

void traversalsToFile(Graph *graph, Str20 startKey, Graph *tree);
void bfs(FILE *fp, Graph *graph, Str20 startKey, Graph *tree); // as per specification, BFS is only required for drawing
void bfsRecursive(FILE *fp, Graph *graph, int currentIndex, int originalIndex, Graph *tree, int verticesAtLevelCount, Str20 verticesAtLevel[]);
void dfs(FILE *fp, Graph *graph, Str20 startKey);
void dfsRecursive(FILE *fp, Graph *graph, int startIndex);
void sortAlphabetically(Graph *graph, int *adjIndices, int count);
void printVisitedMatrix(Graph *graph);

#endif // TRAVERSAL_H