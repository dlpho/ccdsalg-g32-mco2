#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "graph.h"
#include "graph.c"
#include "def.h"

/*
 ! Normal Graph
 *
 *
 *
 *
 */

/*
 ! Binary Tree
 * Generally, the drawing of the graphs will be in this format
 *
 * Note: opted to use = instead of ═ due to overflowing reasons
 *
 *               ╔===========╗
 *               ║<Node Data>║
 *               ╚===========╝
 *           ┌─────────┴─────────┐
 *     ╔===========╗       ╔===========╗
 *     ║<Node Data>║       ║<Node Data>║
 *     ╚===========╝       ╚===========╝
 *  ┌────────┴────────┐ ┌────────┴────────┐
 *  ╧                 ╧ ╧                 ╧
 *  Notes:
 *  1.) <Node Data> width should be odd length
 *  2.) Maximum width should be calculated first before drawing the graph for spacing determination
 *  3.) Width per box is: 2 + <Node Data> length
 *  4.) Minimum spacing between nodes is 7. Excludes null nodes
 *
 *
 */

void printTree(Graph *graph, int rootIndex);
void printNode(Node *node);
void repeatPrint(char c, int n);

int main()
{
    Graph *graph = createGraph(3);
    addVertex(graph, "A");
    addVertex(graph, "B");
    addVertex(graph, "C");
    addEdge(graph, "A", "B");
    addEdge(graph, "A", "C");

    printTree(graph, 0);
    return 0;
}

void printTree(Graph *graph, int rootIndex)
{
}

void printNode(Node *node)
{
    int width = strlen(node->key);
    bool isEven = width % 2 == 0;
    if (isEven)
        width++; // ensure odd

    // print top
    printf("╔");
    repeatPrint('=', width);
    printf("╗\n");

    // print data
    printf("║%s", node->key);
    if (isEven)
        printf(" "); // add filler if necessary
    printf("║\n");

    // print bottom
    printf("╚");
    repeatPrint('=', width);
    printf("╝\n");
}

void repeatPrint(char c, int n)
{
    for (int i = 0; i < n; i++)
        printf("%c", c);
}