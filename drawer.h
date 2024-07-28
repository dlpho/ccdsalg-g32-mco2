#ifndef DRAWER_H
#define DRAWER_H

#include <stdio.h>
#include "def.h"
#include "graph.h"
#include "node.h"

void drawTree(Graph *graph, StrDraw textFileName);
void drawGraph(Graph *graph, StrDraw textFileName);
void printNode(Node *node, int x, int y, FILE *fp);
void printLine(int x1, int y1, int x2, int y2, FILE *fp);
void depthFinder(Graph *graph, int *depthArray, int vertexIndex, int parentIndex);

#endif