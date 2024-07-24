#include <stdio.h>
#include <math.h>
#include "graph.h"
#include "graph.c"

#define NODE_WIDTH 100
#define NODE_HEIGHT 50
#define NODE_PADDING 10
#define FONT_SIZE 12

#define GRAPH_RADIUS 200
#define GRAPH_CENTER_X 300
#define GRAPH_CENTER_Y 300

#define NODE_X_MARGIN 50
#define NODE_Y_MARGIN 50

#define PI 3.14159265359 // M_PI is not importing from math.h for some reason

void drawTree(Graph *graph);
void drawGraph(Graph *graph);
void printNode(Node *node, int x, int y, FILE *fp);
void printLine(int x1, int y1, int x2, int y2, FILE *fp);

void drawGraph(Graph *graph)
{
    // Generate statistics for calculations

    char fileName[20 + 4 + 1]; // 20 char. for file name, 4 char. for ".svg", 1 char. for null terminator
    printf("File name for svg file (20 char. max).\n Warning: If file exists, it will be overwritten.\n");
    printf(">>> ");
    scanf("%s", fileName);

    strcat(fileName, ".svg");
    FILE *fp = fopen(fileName, "w");

    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    printf("Drawing graph...\n");

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
    printf("Graph drawn to %s\n", fileName);
}

void drawTree(Graph *graph)
{
    // Generate statistics for calculations

    char fileName[20 + 4 + 1]; // 20 char. for file name, 4 char. for ".svg", 1 char. for null terminator
    printf("File name for svg file (20 char. max).\n Warning: If file exists, it will be overwritten.\n");
    printf(">>> ");
    scanf("%s", fileName);

    strcat(fileName, ".svg");
    FILE *fp = fopen(fileName, "w");

    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    printf("Drawing tree...\n");

    // Write svg header
    fprintf(fp, "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");

    // Write svg footer
    fprintf(fp, "</svg>");
    fclose(fp);
    printf("Tree drawn to %s\n", fileName);
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

int main()
{
    Graph *graph = createGraph(5);
    Str20 keys[] = {"A", "B", "C", "D", "E"};
    addVertex(graph, keys[0]);
    addVertex(graph, keys[1]);
    addVertex(graph, keys[2]);
    addVertex(graph, keys[3]);
    addVertex(graph, keys[4]);

    addEdge(graph, keys[0], keys[1]);
    addEdge(graph, keys[0], keys[3]);
    addEdge(graph, keys[1], keys[2]);
    addEdge(graph, keys[2], keys[4]);
    addEdge(graph, keys[2], keys[3]);
    addEdge(graph, keys[3], keys[4]);
    addEdge(graph, keys[4], keys[0]);

    drawGraph(graph);

    return 0;
}