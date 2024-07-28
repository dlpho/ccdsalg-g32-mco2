#ifndef DRAWER_C
#define DRAWER_C

#include <stdio.h>
#include <math.h>
#include "graph.h"
#include "graph.c"

#define NODE_WIDTH 100
#define NODE_HEIGHT 50
#define NODE_PADDING 10
#define FONT_SIZE 12

#define GRAPH_RADIUS 400
#define GRAPH_CENTER_X GRAPH_RADIUS
#define GRAPH_CENTER_Y GRAPH_RADIUS

#define NODE_X_MARGIN 50
#define NODE_Y_MARGIN 50

#define PI 3.14159265359 // M_PI is not importing from math.h for some reason

void drawTree(Graph *graph, Str100 textFileName);
void drawGraph(Graph *graph, Str100 textFileName);
void printNode(Node *node, int x, int y, FILE *fp);
void printLine(int x1, int y1, int x2, int y2, FILE *fp);
void depthFinder(Graph *graph, int *depthArray, int vertexIndex, int parentIndex);

void drawGraph(Graph *graph, Str100 textFileName)
{
    // Generate statistics for calculations

    // fileName + fileSuffix + extension + null terminator
    char fileName[100 + 6 + 4 + 1];
    sprintf(fileName, "%s_graph.svg", textFileName);
    FILE *fp = fopen(fileName, "w");

    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    /* Disabled output as precaution to any strict I/O */
    // printf("Drawing graph...\n");

    // Write svg header
    fprintf(fp, "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");

    int numNodes = graph->numVertices;
    // draw edges
    for (int i = 0; i < numNodes; i++)
    {
        for (int j = 0; j < numNodes; j++)
        {
            if (graph->edges[i][j])
            {
                // line should start/end from center of node
                int x1 = GRAPH_CENTER_X + GRAPH_RADIUS * cos(2 * PI * i / numNodes) + NODE_WIDTH / 2;
                int y1 = GRAPH_CENTER_Y + GRAPH_RADIUS * sin(2 * PI * i / numNodes) + NODE_HEIGHT / 2;
                int x2 = GRAPH_CENTER_X + GRAPH_RADIUS * cos(2 * PI * j / numNodes) + NODE_WIDTH / 2;
                int y2 = GRAPH_CENTER_Y + GRAPH_RADIUS * sin(2 * PI * j / numNodes) + NODE_HEIGHT / 2;
                printLine(x1, y1, x2, y2, fp);
            }
        }
    }

    // draw nodes in a circle
    for (int i = 0; i < numNodes; i++)
    {
        int x = GRAPH_CENTER_X + GRAPH_RADIUS * cos(2 * PI * i / numNodes);
        int y = GRAPH_CENTER_Y + GRAPH_RADIUS * sin(2 * PI * i / numNodes);
        printNode(graph->vertices[i], x, y, fp);
    }

    // Write svg footer
    fprintf(fp, "</svg>");
    fclose(fp);
    /* Disabled output as precaution to any strict I/O */
    // printf("Graph drawn to %s\n", fileName);
}

/**
 * ! IMPORTANT ASSUMPTION: First node in graph is the root node
 * ! IMPORTANT ASSUMPTION: Nodes added are in order. i.e. children of Node B is added first before children of Node C
 */
void drawTree(Graph *graph, Str100 textFileName)
{
    int depthOfNode[graph->numVertices];
    int childrenCount[graph->numVertices];
    int depthWidth[graph->numVertices];
    int nodesAtDepthProcessed[graph->numVertices];

    // initialize values to 0
    for (int i = 0; i < graph->numVertices; i++)
    {
        depthOfNode[i] = 0;
        childrenCount[i] = 0;
        depthWidth[i] = 0;
        nodesAtDepthProcessed[i] = 0;
    }

    for (int i = 0; i < graph->numVertices; i++)
    {
        for (int j = 0; j < graph->numVertices; j++)
            if (graph->edges[i][j])
                childrenCount[i]++;
        if (i != 0)             // except for root node
            childrenCount[i]--; // remove parent from children count
    }

    // determine depth of each node
    depthFinder(graph, depthOfNode, 0, -1);

    // count nodes at each depth
    for (int i = 0; i < graph->numVertices; i++)
        depthWidth[depthOfNode[i]]++;

    int widestDepth = 0;
    for (int i = 0; i < graph->numVertices; i++)
        if (depthOfNode[i] > widestDepth)
            widestDepth = depthOfNode[i];

    // fileName + fileSuffix + extension + null terminator
    char fileName[100 + 5 + 4 + 1];
    sprintf(fileName, "%s_tree.svg", textFileName);
    FILE *fp = fopen(fileName, "w");

    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    /* Disabled output as precaution to any strict I/O */
    // printf("Drawing tree...\n");

    // Write svg header
    fprintf(fp, "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");

    int totalWidth = depthWidth[widestDepth] * (NODE_WIDTH + NODE_X_MARGIN) - NODE_X_MARGIN;
    int centerX = totalWidth / 2;
    int nodePositions[graph->numVertices][2];
    for (int i = 0; i < graph->numVertices; i++)
    {
        // Calculate the horizontal position
        int nodesAtCurrentDepth = depthWidth[depthOfNode[i]];
        int processedNodesAtCurrentDepth = nodesAtDepthProcessed[depthOfNode[i]]++;
        int widthOfCurrentDepth = nodesAtCurrentDepth * (NODE_WIDTH + NODE_X_MARGIN) - NODE_X_MARGIN;
        int offsetPerNode = (widthOfCurrentDepth + NODE_X_MARGIN) / nodesAtCurrentDepth;
        int x = centerX;
        x -= widthOfCurrentDepth / 2;
        x += offsetPerNode * processedNodesAtCurrentDepth;

        // Calculate the vertical position
        int y = depthOfNode[i] * (NODE_Y_MARGIN + NODE_HEIGHT);

        nodePositions[i][0] = x;
        nodePositions[i][1] = y;
    }

    for (int i = 0; i < graph->numVertices; i++)
    {
        for (int j = 0; j < graph->numVertices; j++)
        {
            if (graph->edges[i][j] == 1)
            { // Assuming adjMatrix is used to store edges
                int x1 = nodePositions[i][0];
                int y1 = nodePositions[i][1];
                int x2 = nodePositions[j][0];
                int y2 = nodePositions[j][1];
                printLine(x1 + NODE_WIDTH / 2, y1 + NODE_HEIGHT / 2, x2 + NODE_WIDTH / 2, y2 + NODE_HEIGHT / 2, fp);
            }
        }
    }

    // iterate through node positions and print nodes
    for (int i = 0; i < graph->numVertices; i++)
        printNode(graph->vertices[i], nodePositions[i][0], nodePositions[i][1], fp);

    // Write svg footer
    fprintf(fp, "</svg>");
    fclose(fp);
    /* Disabled output as precaution to any strict I/O */
    // printf("Tree drawn to %s\n", fileName);
}

void depthFinder(Graph *graph, int *depthArray, int vertexIndex, int parentIndex)
{
    for (int i = 0; i < graph->numVertices; i++)
    {
        if (graph->edges[vertexIndex][i])
        {
            depthArray[i] = depthArray[vertexIndex] + 1;
            depthFinder(graph, depthArray, i, vertexIndex);
        }
    }
}

/**
 * Prints a rectangular node that can hold text up to 20 characters long
 */
void printNode(Node *node, int x, int y, FILE *fp)
{
    fprintf(fp, "<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" fill=\"white\" stroke=\"black\" />\n", x, y, NODE_WIDTH, NODE_HEIGHT);
    fprintf(fp, "<text x=\"%d\" y=\"%d\" font-size=\"%d\" fill=\"black\">%s</text>\n", x + NODE_PADDING, y + NODE_HEIGHT / 2, FONT_SIZE, node->key);
}

/**
 * Prints a line between two nodes
 */
void printLine(int x1, int y1, int x2, int y2, FILE *fp)
{
    fprintf(fp, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"black\" />\n", x1, y1, x2, y2);
}

#endif